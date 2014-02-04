/*
 * Copyright 2012-2013 Falltergeist Developers.
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
 *
 */

// C++ standard includes
#include <cmath>
#include <iostream>

// Falltergeist includes
#include "../Engine/Location.h"
#include "../Engine/LocationObject.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/Animation.h"
#include "../Engine/Mouse.h"
#include "../Engine/Game.h"
#include "../Game/GameDefines.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameAmmoItemObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameContainerItemObject.h"
#include "../Game/GameDrugItemObject.h"
#include "../Game/GameKeyItemObject.h"
#include "../Game/GameMiscItemObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../Game/GameDoorSceneryObject.h"
#include "../Game/GameElevatorSceneryObject.h"
#include "../Game/GameGenericSceneryObject.h"
#include "../Game/GameStairsSceneryObject.h"
#include "../Game/GameLadderSceneryObject.h"
#include "../Game/GameWallObject.h"
#include "../Game/GameMiscObject.h"
#include "../Game/GameDudeObject.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Location::Location(libfalltergeist::MapFileType * mapFile)
{
    _cols = 100;
    _rows = 100;

    _camera = new LocationCamera(640, 480, 0, 0);

    _mapFile = mapFile;
    _tilesLst = ResourceManager::lstFileType("art/tiles/tiles.lst");
    _tilesBackground = new Surface(640, 480);
    _tilesBackground->fill(0xFF000000);
    init();
}

Location::~Location()
{
    delete _tilesLst;
    delete _camera;

}

LocationCamera * Location::camera()
{
    return _camera;
}

void Location::init()
{
    // Инициализируем положение камеры
    unsigned int defaultPosition = _mapFile->defaultPosition();
    camera()->setXPosition(hexagonToX(defaultPosition));
    camera()->setYPosition(hexagonToY(defaultPosition));

    // Initialize MAP vars
    if (_mapFile->MVARsize() > 0)
    {
        auto name = _mapFile->name();
        auto gam = ResourceManager::gamFileType("maps/" + name.substr(0, name.find(".")) + ".gam");
        for (auto mvar : *gam->MVARS())
        {
            _MVARS.push_back(mvar.second);
        }
    }

    _elevation = _mapFile->defaultElevation();

    std::vector<libfalltergeist::MapObject *> * mapObjects = _mapFile->elevations()->at(_elevation)->objects();

    for (std::vector<libfalltergeist::MapObject *>::iterator it = mapObjects->begin(); it != mapObjects->end(); ++it)
    {
        auto mapObject = *it;
        GameObject* object = createObject(mapObject->PID());

        object->setLocation(this);
        object->setFID( mapObject->FID() );
        object->setPID( mapObject->PID() );
        object->setElevation( mapObject->elevation() );
        object->setOrientation( mapObject->orientation() );
        object->setPosition( mapObject->hexPosition() );

        if (mapObject->scriptId() > 0)
        {
            auto intFile = ResourceManager::intFileType(mapObject->scriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile, object));
        }
        if (mapObject->mapScriptId() > 0 && mapObject->mapScriptId() != mapObject->scriptId())
        {
            auto intFile = ResourceManager::intFileType(mapObject->mapScriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile, object));
        }

        _objects.push_back(object);
    }

    //_player = new GameDudeObject();
    //_player->setName("Choozen One");
    _player = Game::getInstance().player();
    _player->setPID(0x01000001);
    _player->setFID(FID_HERO_MALE);
    _player->setOrientation(_mapFile->defaultOrientation());
    _player->setPosition(_mapFile->defaultPosition());
    //auto script = new VM(ResourceManager::intFileType(0), _player);
    //_player->scripts()->push_back(script);
    _objects.push_back(_player);

    // ON MAP LOADED
    if (_mapFile->scriptId() > 0)
    {
        _script = new VM(ResourceManager::intFileType(_mapFile->scriptId()-1), this);
    }

    // -----------------------
    generateBackground();
    checkObjectsToRender();
}

GameDudeObject* Location::player()
{
    return _player;
}

GameObject* Location::createObject(int PID)
{
    auto proto = ResourceManager::proFileType(PID);
    GameObject* object = 0;
    switch (proto->typeId())
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
        {
            switch(proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_ITEM_AMMO:
                {
                    object = new GameAmmoItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_ARMOR:
                {
                    object = new GameArmorItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_CONTAINER:
                {
                    object = new GameContainerItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_DRUG:
                {
                    object = new GameDrugItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_KEY:
                {
                    object = new GameKeyItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_MISC:
                {
                    object = new GameMiscItemObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_WEAPON:
                {
                    object = new GameWeaponItemObject();
                    break;
                }
            }
            auto msg = ResourceManager::msgFileType("text/english/game/pro_item.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
        case libfalltergeist::ProFileType::TYPE_CRITTER:
        {
            object = new GameCritterObject();
            auto msg = ResourceManager::msgFileType("text/english/game/pro_crit.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            for (unsigned int i = 0; i != 7; ++i)
            {
                ((GameCritterObject*)object)->setStat(i, proto->critterStats()->at(i));
                ((GameCritterObject*)object)->setStatBonus(i, proto->critterStatsBonus()->at(i));
            }
            for (unsigned int i = 0; i != 18; ++i)
            {
                ((GameCritterObject*)object)->setSkill(i, proto->critterSkills()->at(i));
            }
            ((GameCritterObject*)object)->setActionPoints(proto->critterActionPoints());
            ((GameCritterObject*)object)->setHitPointsMax(proto->critterHitPointsMax());
            ((GameCritterObject*)object)->setArmorClass(proto->critterArmorClass());
            ((GameCritterObject*)object)->setCarryWeight(proto->critterCarryWeight());
            ((GameCritterObject*)object)->setMeleeDamage(proto->critterMeleeDamage());
            ((GameCritterObject*)object)->setSequence(proto->critterSequence());
            ((GameCritterObject*)object)->setCriticalChance(proto->critterCriticalChance());
            ((GameCritterObject*)object)->setHealingRate(proto->critterHealingRate());
            break;
        }
        case libfalltergeist::ProFileType::TYPE_SCENERY:
        {
            switch (proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_SCENERY_DOOR:
                {
                    object = new GameDoorSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_ELEVATOR:
                {
                    object = new GameElevatorSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_GENERIC:
                {
                    object = new GameGenericSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_TOP:
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                {
                    object = new GameLadderSceneryObject();
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_STAIRS:
                {
                    object = new GameStairsSceneryObject();
                    break;
                }
            }
            auto msg = ResourceManager::msgFileType("text/english/game/pro_scen.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
        case libfalltergeist::ProFileType::TYPE_WALL:
        {
            object = new GameWallObject();
            auto msg = ResourceManager::msgFileType("text/english/game/pro_wall.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
        case libfalltergeist::ProFileType::TYPE_TILE:
        {
            //auto msg = ResourceManager::msgFileType("text/english/game/pro_tile.msg");
            throw 1;
            //object->setName(msg->message(proto->messageId())->text());
            break;
        }
        case libfalltergeist::ProFileType::TYPE_MISC:
        {
            object = new GameMiscObject();
            auto msg = ResourceManager::msgFileType("text/english/game/pro_misc.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}
            break;
        }
    }
    object->setPID(PID);
    if (proto->scriptId() > 0)
    {
        auto intFile = ResourceManager::intFileType(proto->scriptId());
        if (intFile) object->scripts()->push_back(new VM(intFile, object));
    }

    return object;
}

void Location::handleAction(GameObject* object, int action)
{
    /*
    switch (action)
    {

        case Mouse::ICON_ROTATE:
        {
            auto dude = dynamic_cast<GameDudeObject*>(object);
            if (!dude) break; //throw Exception("LocationState::handleAction() - only Dude can be rotated");

            int orientation = dude->orientation() + 1;
            if (orientation > 5) orientation = 0;
            dude->setOrientation(orientation);

            break;
        }
        case Mouse::ICON_TALK:
        {
            for(auto script : *object->scripts())
            {
                script->call("talk_p_proc");
            }
        }

    }*/
}

void Location::think()
{

    if (!_initialized)
    {
        _initialized = true;
        if (_script) _script->initialize();
        if (_script) _script->call("map_enter_p_proc");

        for (auto object : _objects)
        {
            // initialize scripts
            for (auto script : *object->scripts()) script->initialize();

            // map_enter_p_proc
            for (auto script : *object->scripts()) script->call("map_enter_p_proc");
        }

    }
    else
    {
        if (_scriptsTicks + 500 < SDL_GetTicks())
        {
            _scriptsTicks = SDL_GetTicks();
            for (auto object : _objects)
            {
                for (auto script : *object->scripts())
                {
                    script->call("map_update_p_proc");
                    script->call("look_at_p_proc");
                    script->call("description_p_proc");
                    script->call("critter_p_proc");
                    //script->call("timed_event_p_proc");
                }
             }
        }

        for (auto object : _objects)
        {
            if (Animation* animation = object->animationQueue()->animation())
            {
                animation->think();
            }
        }
    }
}


void Location::checkObjectsToRender()
{
    _objectsToRender.clear();

    for (GameObject* object : _objects)
    {
        if (!object->surface() && !object->animationQueue()->animation()) continue;

        int x,y, width, height;
        if (Animation* animation = object->animationQueue()->animation())
        {
            x = Location::hexagonToX(object->position()) + animation->xOffset() - animation->surfaces()->at(0)->width()/2;
            y = Location::hexagonToY(object->position()) + animation->yOffset() - animation->surfaces()->at(0)->height();
            width = animation->width();
            height = animation->height();
        }
        else
        {
            Surface* surface = object->surface();
            x = Location::hexagonToX(object->position()) + surface->xOffset() - surface->width()/2;
            y = Location::hexagonToY(object->position()) + surface->yOffset() - surface->height();
            width = surface->width();
            height = surface->height();
        }

        // check if object is out of camera borders
        if (x + width < camera()->x()) continue; // right
        if (y + height < camera()->y()) continue; // bottom
        if (x > camera()->x() + camera()->width()) continue; // left
        if (y > camera()->y() + camera()->height()) continue; // top

        _objectsToRender.push_back(object);
    }
}

void Location::generateBackground()
{
    _tilesBackground->fill(0xFF000000);
    // Инициализируем тайловый фон
    for (unsigned int i = 0; i != _cols*_rows; ++i)
    {
        int tileX = tileToX(i);
        int tileY = tileToY(i);

        // Проверяем не выходят ли тайлы за пределы зоны видимости
        if (tileX + TILE_WIDTH < camera()->x()) continue;
        if (tileX > camera()->x() + camera()->width()) continue;
        if (tileY + TILE_HEIGHT < camera()->y()) continue;
        if (tileY > camera()->y() + camera()->height()) continue;

        std::string frmName = _tilesLst->strings()->at(_mapFile->elevations()->at(_elevation)->floorTiles()->at(i));
        Surface * tile = ResourceManager::surface("art/tiles/" + frmName);
        tile->setX(tileX - camera()->x());
        tile->setY(tileY - camera()->y());
        tile->blit(_tilesBackground);
    }

    /*
    int x1 = hexagonToX(_mapFile->defaultPosition()) - camera()->x();
    int y1 = hexagonToY(_mapFile->defaultPosition()) - camera()->y();
    int x2 = hexagonToX(_mapFile->defaultPosition() + 2) - camera()->x();
    int y2 = hexagonToY(_mapFile->defaultPosition() + 2) - camera()->y();
    _tilesBackground->drawLine(x1, y1, x2, y2, 0xFFFF0000);
    _tilesBackground->drawLine(319, 0, 319, 479, 0xFF00FF00);
    _tilesBackground->drawLine(0, 239, 639, 239, 0xFF00FF00);
    */
}

int Location::hexagonToX(unsigned int hexagon)
{
    unsigned int cols = 100;
    unsigned int a = hexagon % 200;
    unsigned int b = ceil(hexagon/200);
    hexagon = a*200 + b;

    unsigned int y = ceil(hexagon/200);
    int centerX = 48*(cols-1) + 48 + 16*(hexagon%200) - 24*y;

        if ((hexagon/200)%2 == 1)
        {
            centerX -= 8;
        }
    return centerX + 17;
}

int Location::hexagonToY(unsigned int hexagon)
{
    unsigned int a = hexagon % 200;
    unsigned int b = ceil(hexagon/200);
    hexagon = a*200 + b;

    unsigned int y = ceil(hexagon/200);
    int centerY = (hexagon%200)*12 + 6*y ;

        if ((hexagon/200)%2 == 1)
        {
            centerY -= 6;
        }
    return centerY + 12;

}

unsigned int Location::positionToHexagon(int x, int y)
{
    for (unsigned int i = 0; i != 200*200; ++i)
    {
        int hX = hexagonToX(i);
        int hY = hexagonToY(i);

       if (y >= hY - 8 && y < hY + 4)
       if (x >= hX - 16 && x < hX + 16)
       {
           return i;
       }
    }
    return 0;
}

libfalltergeist::MapFileType * Location::mapFile()
{
    return _mapFile;
}

unsigned int Location::tileToX(unsigned int tile)
{
    return (_cols - tile % _cols - 1)*48 + 32*ceil(tile / _cols);
}

unsigned int Location::tileToY(unsigned int tile)
{
    return ceil(tile / _cols)*24 + (tile % _cols)*12;
}

Surface * Location::tilesBackground()
{
    return _tilesBackground;
}

bool Location::scroll(bool up, bool down, bool left, bool right)
{    
    if (SDL_GetTicks() < _scrollTicks + 10) return _scrollStatus;
    _scrollTicks = SDL_GetTicks();

    _scrollStatus = false;
    int scrollDelta = 5;

    if (up && camera()->y() >= scrollDelta)
    {
        camera()->setYPosition(camera()->yPosition() - scrollDelta);
        _scrollStatus = true;
    }
    if (left && camera()->x() >= scrollDelta)
    {
        camera()->setXPosition(camera()->xPosition() - scrollDelta);
        _scrollStatus = true;
    }
    if (down)
    {

        if (camera()->yPosition() < height() - scrollDelta - camera()->height())
        {
            camera()->setYPosition(camera()->yPosition() + scrollDelta);
            _scrollStatus = true;
        }
    }
    if (right)
    {
        if (camera()->x() < width() - scrollDelta - camera()->width())
        {
            camera()->setXPosition(camera()->xPosition() + scrollDelta);
            _scrollStatus = true;
        }
    }

    if (_scrollStatus)
    {
        generateBackground();
        checkObjectsToRender();
    }
    return _scrollStatus;
}

std::vector<GameObject*>* Location::objects()
{
    return &_objects;
}

std::vector<GameObject*>* Location::objectsToRender()
{
    return &_objectsToRender;
}

int Location::width()
{
    return 48*_cols + 32*_rows;
}

int Location::height()
{
    return 12*_cols + 24*_rows;
}

void Location::setMVAR(unsigned int number, int value)
{
    if (number >= _MVARS.size())
    {
        throw Exception("Location::setMVAR(num, value) - num out of range: " + std::to_string((int)number));
    }
    _MVARS.at(number) = value;
}

int Location::MVAR(unsigned int number)
{
    if (number >= _MVARS.size())
    {
        throw Exception("Location::MVAR(num) - num out of range: " + std::to_string((int)number));
    }
    return _MVARS.at(number);
}

std::map<std::string, VMStackValue*>* Location::EVARS()
{
    return &_EVARS;
}

}
