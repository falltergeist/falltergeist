/*
 * Copyright 2012-2018 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../Helpers/GameObjectHelper.h"

#include "../Exception.h"
#include "../Format/Map/Object.h"
#include "../Format/Map/Script.h"
#include "../Format/Msg/File.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/CritterObject.h"
#include "../Game/DoorSceneryObject.h"
#include "../Game/ExitMiscObject.h"
#include "../Game/ObjectFactory.h"
#include "../Game/SpatialObject.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Helpers
    {
        Game::Object* GameObjectHelper::createFromMapSpatialScript(const Format::Map::Script& mapScript) const
        {
            auto tile = mapScript.spatialTile();
            auto hex = tile & 0xFFFF;
            auto elev = ((tile >> 28) & 0xf) >> 1;

            auto object = new Game::SpatialObject(mapScript.spatialRadius());
            object->setElevation(elev);
            object->setPosition(hex);

            auto intFile = ResourceManager::getInstance()->intFileType(mapScript.scriptId());
            if (intFile) {
                object->setScript(new VM::Script(intFile, object));
            }
            return object;
        }

        Game::Object* GameObjectHelper::createFromMapObject(const std::unique_ptr<Format::Map::Object> &mapObject) const
        {
            auto object = Game::ObjectFactory::getInstance()->createObject(mapObject->PID());
            if (!object) {
                Logger::error() << "Location::setLocation() - can't create object with PID: " << mapObject->PID() << std::endl;
                return nullptr;
            }

            object->setFID(mapObject->FID());
            object->setElevation(mapObject->elevation());
            object->setOrientation(mapObject->orientation());
            object->setPosition(mapObject->hexPosition());
            object->setLightRadius(mapObject->lightRadius());
            object->setLightIntensity(mapObject->lightIntensity());
            object->setFlags(mapObject->flags());
            object->setDefaultFrame(mapObject->frameNumber());

            if (auto exitGrid = dynamic_cast<Game::ExitMiscObject *>(object)) {
                exitGrid->setExitMapNumber(mapObject->exitMap());
                exitGrid->setExitElevationNumber(mapObject->exitElevation());
                exitGrid->setExitHexagonNumber(mapObject->exitPosition());
                exitGrid->setExitDirection(mapObject->exitOrientation());
            }

            if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                door->setOpened(mapObject->opened());
            }

            if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                for (auto &child : mapObject->children()) {
                    auto item = dynamic_cast<Game::ItemObject *>(Game::ObjectFactory::getInstance()->createObject(child->PID()));
                    if (!item) {
                        Logger::error() << "Location::setLocation() - can't create object with PID: " << child->PID() << std::endl;
                        return nullptr;
                    }
                    item->setAmount(child->ammount());
                    container->inventory()->push_back(item);
                }
            }

            // TODO: use common interface...
            if (auto critter = dynamic_cast<Game::CritterObject *>(object)) {
                for (auto &child : mapObject->children()) {
                    auto item = dynamic_cast<Game::ItemObject *>(Game::ObjectFactory::getInstance()->createObject(
                            child->PID()));
                    if (!item) {
                        Logger::error() << "Location::setLocation() - can't create object with PID: "
                                        << child->PID() << std::endl;
                        return nullptr;
                    }
                    item->setAmount(child->ammount());
                    critter->inventory()->push_back(item);
                }
            }

            if (mapObject->scriptId() > 0) {
                auto intFile = ResourceManager::getInstance()->intFileType(mapObject->scriptId());
                if (intFile) {
                    object->setScript(new VM::Script(intFile, object));
                    object->setSID(mapObject->scriptId());
                }
            }
            if (mapObject->mapScriptId() > 0 && mapObject->mapScriptId() != mapObject->scriptId()) {
                auto intFile = ResourceManager::getInstance()->intFileType(mapObject->mapScriptId());
                if (intFile) {
                    object->setScript(new VM::Script(intFile, object));
                    object->setSID(mapObject->mapScriptId());
                }
            }

            if (object->SID() > 0) {
                auto msg = ResourceManager::getInstance()->msgFileType("text/english/game/scrname.msg");
                try {
                    object->setScrName(msg->message(object->SID() + 101)->text());
                }
                catch (const Exception &) {
                }
            }
            return object;
        }
    }
}