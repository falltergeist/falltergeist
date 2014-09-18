/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Graphics/Texture.h"
#include "../Engine/Hexagon.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Game/GameAmmoItemObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameContainerItemObject.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameDefines.h"
#include "../Game/GameDoorSceneryObject.h"
#include "../Game/GameDrugItemObject.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameElevatorSceneryObject.h"
#include "../Game/GameGenericSceneryObject.h"
#include "../Game/GameKeyItemObject.h"
#include "../Game/GameLadderSceneryObject.h"
#include "../Game/GameMiscItemObject.h"
#include "../Game/GameMiscObject.h"
#include "../Game/GameStairsSceneryObject.h"
#include "../Game/GameWallObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../UI/Image.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Location::Location(std::shared_ptr<libfalltergeist::MapFileType> mapFile)
{
    _mapFile = mapFile;
    init();
}

Location::~Location()
{
}

std::shared_ptr<LocationCamera> Location::camera()
{
    return _camera;
}

std::shared_ptr<Texture> Location::tilesFloor()
{
    return _tilesFloor;
}

std::shared_ptr<Texture> Location::tilesRoof()
{
    return _tilesRoof;
}

void Location::init()
{
    _elevation = _mapFile->defaultElevation();

    _tilesLst = ResourceManager::lstFileType("art/tiles/tiles.lst");

    unsigned int i = 0;
    for (unsigned int x = 0; x != 200; ++x)
    {
        for (unsigned int y = 0; y != 200; ++y, ++i)
        {
            auto hexagon = std::shared_ptr<Hexagon>(new Hexagon(i));
            _hexagons.push_back(hexagon);
            _hexagons.back()->setX(x);
            _hexagons.back()->setY(y);
        }
    }

    for (auto i = 0; i != 200*200; ++i)
    {
        auto hexagon = hexagons()->at(i);
        auto size = hexagons()->size();
        auto cols = 200;
        unsigned int index1 = (hexagon->y() * cols) + hexagon->x() + 1;
        if (index1 < size) hexagon->neighbours()->push_back(hexagons()->at(index1));

        unsigned int index2 = ((hexagon->y() + 1) * cols) + hexagon->x() + 1;
        if (index2 < size) hexagon->neighbours()->push_back(hexagons()->at(index2));

        unsigned int index3 = ((hexagon->y() - 1) * cols) + hexagon->x();
        if (index3 < size) hexagon->neighbours()->push_back(hexagons()->at(index3));

        unsigned int index4 = (hexagon->y() * cols) + hexagon->x() - 1;
        if (index4 < size) hexagon->neighbours()->push_back(hexagons()->at(index4));

        unsigned int index5 = ((hexagon->y() + 1) * cols) + hexagon->x() - 1;
        if (index5 < size) hexagon->neighbours()->push_back(hexagons()->at(index5));

        unsigned int index6 = ((hexagon->y() + 1) * cols) + hexagon->x();
        if (index6 < size) hexagon->neighbours()->push_back(hexagons()->at(index6));

    }

    // Генерируем изображение пола
    _generateFloor();
    _generateRoof();

    auto game = Game::getInstance();

    _camera = std::shared_ptr<LocationCamera>(new LocationCamera(game->renderer()->width(), game->renderer()->height(), 0, 0));

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

    auto mapObjects = _mapFile->elevations()->at(_elevation)->objects();

    for (auto mapObject : *mapObjects)
    {
        auto object = createObject(mapObject->PID());
        if (!object) continue;


        object->setLocation(this);
        object->setFID( mapObject->FID() );
        object->setPID( mapObject->PID() );
        object->setElevation( mapObject->elevation() );
        object->setOrientation( mapObject->orientation() );
        object->setPosition( mapObject->hexPosition() );

        if (mapObject->scriptId() > 0)
        {
            auto intFile = ResourceManager::intFileType(mapObject->scriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile,object));
        }
        if (mapObject->mapScriptId() > 0 && mapObject->mapScriptId() != mapObject->scriptId())
        {
            auto intFile = ResourceManager::intFileType(mapObject->mapScriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile, object));
        }

        _objects.push_back(object);
    }

    _player = Game::getInstance()->player();
    //_player->setName("Choozen One");
    //_player = Game::getInstance().player();
    _player->setPID(0x01000001);
    _player->setFID(FID_HERO_MALE);
    _player->setOrientation(_mapFile->defaultOrientation());
    _player->setPosition(_mapFile->defaultPosition());

    // ??????
    auto script = new VM(ResourceManager::intFileType(0), _player);
    _player->scripts()->push_back(script);


    _objects.push_back(_player);

    // Just for testing
    {
        auto armor = createObject(0x00000003); // powered armor
        _player->setArmorSlot(std::dynamic_pointer_cast<GameArmorItemObject>(armor));
        auto leftHand = createObject(0x0000000C); // minigun
        _player->setLeftHandSlot(std::dynamic_pointer_cast<GameWeaponItemObject>(leftHand));

        auto rightHand = createObject(0x00000007); // spear
        _player->setRightHandSlot(std::dynamic_pointer_cast<GameWeaponItemObject>(rightHand));
    }

    std::cout << _player->position() << std::endl;
    std::shared_ptr<Hexagon> hexagon = hexagons()->at(_player->position());

    for (auto neighbor : *hexagon->neighbours())
    {
        //auto object = std::shared_ptr<GameDudeObject>(new GameDudeObject());
        //object->setPID(0x01000001);
        //object->setFID(FID_HERO_MALE);
        //object->setOrientation(_mapFile->defaultOrientation());
        //object->setPosition(neighbor->number());
        //_objects.push_back(object);
        std::cout << neighbor->number() << std::endl;
    }

    //throw 1;


    // ON MAP LOADED
    if (_mapFile->scriptId() > 0)
    {
        _script = new VM(ResourceManager::intFileType(_mapFile->scriptId()-1), Game::getInstance()->location());
    }

    checkObjectsToRender();
}

void Location::_generateFloor()
{
    unsigned int tilesWidth = 48*_cols + 32*_rows;
    unsigned int tilesHeight = 12*_cols + 24*_rows;

    _tilesFloor = std::shared_ptr<Texture>(new Texture(tilesWidth, tilesHeight));
    _tilesFloor->fill(0x000000FF);

    for (unsigned int i = 0; i != _cols*_rows; ++i)
    {
        std::string frmName = _tilesLst->strings()->at(_mapFile->elevations()->at(_elevation)->floorTiles()->at(i));
        auto tile = std::shared_ptr<Image>(new Image("art/tiles/" + frmName));
        tile->texture()->blitTo(_tilesFloor, tileToX(i), tileToY(i));
    }
}

void Location::_generateRoof()
{
    unsigned int tilesWidth = 48*_cols + 32*_rows;
    unsigned int tilesHeight = 12*_cols + 24*_rows;

    _tilesRoof = std::shared_ptr<Texture>(new Texture(tilesWidth, tilesHeight));
    for (unsigned int i = 0; i != _cols*_rows; ++i)
    {
        std::string frmName = _tilesLst->strings()->at(_mapFile->elevations()->at(_elevation)->roofTiles()->at(i));
        auto tile = std::shared_ptr<Image>(new Image("art/tiles/" + frmName));
        tile->texture()->blitTo(_tilesRoof, tileToX(i), tileToY(i));
    }
}

std::shared_ptr<GameObject> Location::createObject(int PID)
{
    auto proto = ResourceManager::proFileType(PID);
    std::shared_ptr<GameObject> object;
    switch (proto->typeId())
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
        {
            switch(proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_ITEM_AMMO:
                {
                    object = std::shared_ptr<GameAmmoItemObject>(new GameAmmoItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_ARMOR:
                {
                    object = std::shared_ptr<GameArmorItemObject>(new GameArmorItemObject());
                    for (unsigned int i = 0; i != 9; ++i)
                    {
                        ((GameArmorItemObject*)object.get())->setDamageResist(i, proto->damageResist()->at(i));
                        ((GameArmorItemObject*)object.get())->setDamageThreshold(i, proto->damageThreshold()->at(i));
                    }
                    ((GameArmorItemObject*)object.get())->setPerk(proto->perk());
                    ((GameArmorItemObject*)object.get())->setMaleFID(proto->armorMaleFID());
                    ((GameArmorItemObject*)object.get())->setFemaleFID(proto->armorFemaleFID());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_CONTAINER:
                {
                    object = std::shared_ptr<GameContainerItemObject>(new GameContainerItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_DRUG:
                {
                    object = std::shared_ptr<GameDrugItemObject>(new GameDrugItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_KEY:
                {
                    object = std::shared_ptr<GameKeyItemObject>(new GameKeyItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_MISC:
                {
                    object = std::shared_ptr<GameMiscItemObject>(new GameMiscItemObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_ITEM_WEAPON:
                {
                    object = std::shared_ptr<GameWeaponItemObject>(new GameWeaponItemObject());

                    ((GameWeaponItemObject*)object.get())->setPerk(proto->perk());
                    ((GameWeaponItemObject*)object.get())->setAnimationCode(proto->weaponAnimationCode());
                    ((GameWeaponItemObject*)object.get())->setDamageMin(proto->weaponDamageMin());
                    ((GameWeaponItemObject*)object.get())->setDamageMax(proto->weaponDamageMax());
                    ((GameWeaponItemObject*)object.get())->setDamageType(proto->weaponDamageType());
                    ((GameWeaponItemObject*)object.get())->setRangePrimary(proto->weaponRangePrimary());
                    ((GameWeaponItemObject*)object.get())->setRangeSecondary(proto->weaponRangeSecondary());
                    ((GameWeaponItemObject*)object.get())->setMinimumStrenght(proto->weaponMinimumStrenght());
                    ((GameWeaponItemObject*)object.get())->setActionCostPrimary(proto->weaponActionCostPrimary());
                    ((GameWeaponItemObject*)object.get())->setActionCostSecondary(proto->weaponActionCostSecondary());
                    ((GameWeaponItemObject*)object.get())->setBurstRounds(proto->weaponBurstRounds());
                    ((GameWeaponItemObject*)object.get())->setAmmoType(proto->weaponAmmoType());
                    ((GameWeaponItemObject*)object.get())->setAmmoPID(proto->weaponAmmoPID());
                    ((GameWeaponItemObject*)object.get())->setAmmoCapacity(proto->weaponAmmoCapacity());
                    break;
                }
            }
            ((GameItemObject*)object.get())->setWeight(proto->weight());
            ((GameItemObject*)object.get())->setInventoryFID(proto->inventoryFID());
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
            object = std::shared_ptr<GameCritterObject>(new GameCritterObject());
            auto msg = ResourceManager::msgFileType("text/english/game/pro_crit.msg");
            try
            {
                object->setName(msg->message(proto->messageId())->text());
                object->setDescription(msg->message(proto->messageId() + 1)->text());
            }
            catch (libfalltergeist::Exception) {}

            for (unsigned int i = 0; i != 7; ++i)
            {
                ((GameCritterObject*)object.get())->setStat(i, proto->critterStats()->at(i));
                ((GameCritterObject*)object.get())->setStatBonus(i, proto->critterStatsBonus()->at(i));
            }
            for (unsigned int i = 0; i != 18; ++i)
            {
                ((GameCritterObject*)object.get())->setSkill(i, proto->critterSkills()->at(i));
            }
            ((GameCritterObject*)object.get())->setActionPoints(proto->critterActionPoints());
            ((GameCritterObject*)object.get())->setHitPointsMax(proto->critterHitPointsMax());
            ((GameCritterObject*)object.get())->setArmorClass(proto->critterArmorClass());
            ((GameCritterObject*)object.get())->setCarryWeightMax(proto->critterCarryWeightMax());
            ((GameCritterObject*)object.get())->setMeleeDamage(proto->critterMeleeDamage());
            ((GameCritterObject*)object.get())->setSequence(proto->critterSequence());
            ((GameCritterObject*)object.get())->setCriticalChance(proto->critterCriticalChance());
            ((GameCritterObject*)object.get())->setHealingRate(proto->critterHealingRate());
            for (unsigned int i = 0; i != 9; ++i)
            {
                ((GameCritterObject*)object.get())->setDamageResist(i, proto->damageResist()->at(i));
                ((GameCritterObject*)object.get())->setDamageThreshold(i, proto->damageThreshold()->at(i));
            }
            break;
        }
        case libfalltergeist::ProFileType::TYPE_SCENERY:
        {
            switch (proto->subtypeId())
            {
                case libfalltergeist::ProFileType::TYPE_SCENERY_DOOR:
                {
                    object = std::shared_ptr<GameDoorSceneryObject>(new GameDoorSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_ELEVATOR:
                {
                    object = std::shared_ptr<GameElevatorSceneryObject>(new GameElevatorSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_GENERIC:
                {
                    object = std::shared_ptr<GameGenericSceneryObject>(new GameGenericSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_TOP:
                case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                {
                    object = std::shared_ptr<GameLadderSceneryObject>(new GameLadderSceneryObject());
                    break;
                }
                case libfalltergeist::ProFileType::TYPE_SCENERY_STAIRS:
                {
                    object = std::shared_ptr<GameStairsSceneryObject>(new GameStairsSceneryObject());
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
            object = std::shared_ptr<GameWallObject>(new GameWallObject());
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
            object = std::shared_ptr<GameMiscObject>(new GameMiscObject());
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
    object->setFID(proto->FID());
    object->setCanWalkThru(proto->flags()&0x00000010);

    if (proto->scriptId() > 0)
    {
        auto intFile = ResourceManager::intFileType(proto->scriptId());
        if (intFile) object->scripts()->push_back(new VM(intFile, object));
    }

    return object;
}

void Location::handleAction(GameObject* object, int action)
{
    switch (action)
    {

        case Mouse::ICON_ROTATE:
        {
            auto dude = dynamic_cast<GameDudeObject*>(object);
            if (!dude) throw Exception("LocationState::handleAction() - only Dude can be rotated");

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

    }
}

void Location::think()
{
    if (SDL_GetTicks() - _lastObjectsCheck >= 10)
    {
        _lastObjectsCheck = SDL_GetTicks();
        checkObjectsToRender();
    }

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

    }

}


void Location::checkObjectsToRender()
{
    _objectsToRender.clear();

    for (auto object : _objects)
    {
        auto ui = std::dynamic_pointer_cast<ActiveUI>(object->ui());
        if (!ui) continue;

        unsigned int x, y, width, height;

        width = ui->width();
        height = ui->height();

        auto animation = std::dynamic_pointer_cast<Animation>(object->ui());
        if (animation)
        {
            x = Location::hexagonToX(object->position()) + ui->xOffset() - std::floor(width*0.5);
            y = Location::hexagonToY(object->position()) + ui->yOffset() - height;
        }
        else
        {
            x = Location::hexagonToX(object->position()) + ui->xOffset();
            y = Location::hexagonToY(object->position()) + ui->yOffset();
        }

        // check if object is out of camera borders
        if (x + width < camera()->x()) continue; // right
        if (y + height < camera()->y()) continue; // bottom
        if (x > camera()->x() + camera()->width()) continue; // left
        if (y > camera()->y() + camera()->height()) continue; // top

        ui->setX(Location::hexagonToX(object->position()) - camera()->x());
        ui->setY(Location::hexagonToY(object->position())- camera()->y());


        _objectsToRender.push_back(object);
    }
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

std::shared_ptr<libfalltergeist::MapFileType> Location::mapFile()
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

std::vector<std::shared_ptr<GameObject>>* Location::objects()
{
    return &_objects;
}

std::vector<std::shared_ptr<GameObject>>* Location::objectsToRender()
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

std::map<std::string, std::shared_ptr<VMStackValue>>* Location::EVARS()
{
    return &_EVARS;
}

std::vector<std::shared_ptr<Hexagon>>* Location::hexagons()
{
    return &_hexagons;
}

}
