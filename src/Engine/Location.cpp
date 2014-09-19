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
#include "../Game/GameDefines.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Engine/Game.h"
#include "../Engine/Exception.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../States/LocationState.h"
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


void Location::init()
{
    _elevation = _mapFile->defaultElevation();

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

    auto mapObjects = _mapFile->elevations()->at(_elevation)->objects();

    for (auto mapObject : *mapObjects)
    {
        auto object = GameObjectFactory::createObject(mapObject->PID());
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
        auto armor = GameObjectFactory::createObject(0x00000003); // powered armor
        _player->setArmorSlot(std::dynamic_pointer_cast<GameArmorItemObject>(armor));
        auto leftHand = GameObjectFactory::createObject(0x0000000C); // minigun
        _player->setLeftHandSlot(std::dynamic_pointer_cast<GameWeaponItemObject>(leftHand));

        auto rightHand = GameObjectFactory::createObject(0x00000007); // spear
        _player->setRightHandSlot(std::dynamic_pointer_cast<GameWeaponItemObject>(rightHand));
    }

    // ON MAP LOADED
    if (_mapFile->scriptId() > 0)
    {
        _script = new VM(ResourceManager::intFileType(_mapFile->scriptId()-1), Game::getInstance()->location());
    }

    //Game::getInstance()->locationState()->checkObjectsToRender();
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
        Game::getInstance()->locationState()->checkObjectsToRender();
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



int Location::hexagonToX(unsigned int hexagon)
{
    unsigned int p = hexagon % 200;
    unsigned int q = ceil(hexagon/200);

    int centerX = 48*100 + 16*(q + 1) - 24*p;
    if (p&1) centerX -= 8;

    return centerX;
}

int Location::hexagonToY(unsigned int hexagon)
{
    unsigned int p = hexagon % 200;
    unsigned int q = ceil(hexagon/200);

    int centerY = (q + 1)*12 + 6*p;
    if (p&1) centerY -= 6;

    return centerY;

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

std::vector<std::shared_ptr<GameObject>>* Location::objects()
{
    return &_objects;
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

}
