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
        GameObject* object = 0;

        switch (mapObject->objectTypeId())
        {
            case libfalltergeist::ProFileType::TYPE_ITEM:
            {
                switch(mapObject->objectSubtypeId())
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
                break;
            }
            case libfalltergeist::ProFileType::TYPE_CRITTER:
            {
                object = new GameCritterObject();
                break;
            }
            case libfalltergeist::ProFileType::TYPE_SCENERY:
            {
                switch (mapObject->objectSubtypeId())
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
                    case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                    {
                        throw 0;
                        break;
                    }
                    case libfalltergeist::ProFileType::TYPE_SCENERY_LADDER_TOP:
                    {
                        throw 0;
                        break;
                    }
                    case libfalltergeist::ProFileType::TYPE_SCENERY_STAIRS:
                    {
                        object = new GameStairsSceneryObject();
                        break;
                    }
                }
                break;
            }
            case libfalltergeist::ProFileType::TYPE_WALL:
            {
                object = new GameWallObject();
                break;
            }
            case libfalltergeist::ProFileType::TYPE_TILE:
            {
                throw 1;
                break;
            }
            case libfalltergeist::ProFileType::TYPE_MISC:
            {
                object = new GameMiscObject();
                break;
            }
        }

        object->setLocation(this);
        object->setFID( mapObject->FID() );
        object->setPID( mapObject->PID() );
        object->setElevation( mapObject->elevation() );
        object->setOrientation( mapObject->orientation() );
        object->setPosition( mapObject->hexPosition() );

        auto frm = ResourceManager::frmFileType(object->FID());
        if (frm)
        {
            auto id = mapObject->objectId();
            auto type = mapObject->objectTypeId();
            if (type == 5 && id == 12) continue; // Map scroll blockers
            if (type == 5 && id >= 16 && id <= 23) // exit tiles
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }

            if (frm->framesPerSecond() > 0)
            {
                auto animation = new Animation(frm);
                animation->setCurrentSurfaceSet(object->orientation());
                animation->setX(hexagonToX(object->position()));
                animation->setY(hexagonToY(object->position()));
                object->animationQueue()->add(animation);
            }
            else
            {
                auto surface = new InteractiveSurface(frm, object->orientation());
                surface->setX(hexagonToX(object->position()));
                surface->setY(hexagonToY(object->position()));
                object->setSurface(surface);
            }
        }

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
        auto proto = ResourceManager::proFileType(object->PID());
        if (proto->scriptId() > 0)
        {
            auto intFile = ResourceManager::intFileType(proto->scriptId());
            if (intFile) object->scripts()->push_back(new VM(intFile, object));
        }

        //object->setDescriptionId(ResourceManager::proFileType(mapObject->PID())->messageId());

        _objects.push_back(object);
    }

    _player = new GameDudeObject();
    _player->setPID(0x01000040);
    _player->setFID(0x01000040);
    _player->setOrientation(_mapFile->defaultOrientation());
    _player->setPosition(_mapFile->defaultPosition());
    auto script = new VM(ResourceManager::intFileType(0), _player);
    _player->scripts()->push_back(script);
    _objects.push_back(_player);

    // ON MAP LOADED
    if (_mapFile->scriptId() > 0)
    {
        _script = new VM(ResourceManager::intFileType(_mapFile->scriptId()-1), this);
    }

    // -----------------------
    _generateBackground();
    _checkObjectsToRender();
}

GameDudeObject* Location::player()
{
    return _player;
}

void Location::think()
{
    if (!_initialized)
    {
        _initialized = true;
        if (_script) _script->initialize();

        // initialize scripts
        for (auto object : _objects) for (auto script : *object->scripts()) script->initialize();

        // map_enter_p_proc
        if (_script) _script->call("map_enter_p_proc");
        for (auto object : _objects) for (auto script : *object->scripts()) script->call("map_enter_p_proc");

    }
    else
    {
        for (auto object : _objects) for (auto script : *object->scripts())
        {
            script->call("map_update_p_proc");
        }
    }

}


void Location::_checkObjectsToRender()
{
    _objectsToRender.clear();

    for (auto object : _objects)
    {
        if (!object->surface()) continue;
        // if object is out of camera borders        
        if (object->surface()->x() + object->surface()->xOffset() + object->surface()->width() < camera()->x()) continue;
        if (object->surface()->y() + object->surface()->yOffset() + object->surface()->height() < camera()->y()) continue;

        if (object->surface()->x() + object->surface()->xOffset() > camera()->x() + camera()->width()) continue;
        if (object->surface()->y() + object->surface()->yOffset() > camera()->y() + camera()->height()) continue;

        if (object->animationQueue()->queue()->size() > 0)
        {
            //if (object->x()  - object->animation()->surfaces()->at(0)->width()/2 + object->animation()->xOffsetMin() > camera()->x() + camera()->width()) continue;
            if (object->surface()->x() + object->surface()->xOffset() > camera()->x() + camera()->width()) continue;
            if (object->surface()->y() + object->surface()->yOffset() > camera()->y() + camera()->height()) continue;
        }
        else
        {
            if (object->surface()->x() + object->surface()->xOffset() > camera()->x() + camera()->width()) continue;
            if (object->surface()->y() + object->surface()->yOffset() > camera()->y() + camera()->height()) continue;
        }

        _objectsToRender.push_back(object);
    }
}

void Location::_generateBackground()
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
    bool changed = false;

    int scrollDelta = 5;

    if (up)
    {
        if (camera()->y() >= scrollDelta)
        {
            camera()->setYPosition(camera()->yPosition() - scrollDelta);
            changed = true;
        }
    }
    if (left)
    {
        if (camera()->x() >= scrollDelta)
        {
            camera()->setXPosition(camera()->xPosition() - scrollDelta);
            changed = true;
        }
    }
    if (down)
    {

        if (camera()->yPosition() < height() - scrollDelta - camera()->height())
        {
            camera()->setYPosition(camera()->yPosition() + scrollDelta);
            changed = true;
        }
    }
    if (right)
    {
        if (camera()->x() < width() - scrollDelta - camera()->width())
        {
            camera()->setXPosition(camera()->xPosition() + scrollDelta);
            changed = true;
        }
    }

    if (changed)
    {
        _generateBackground();
        _checkObjectsToRender();
    }
    return changed;
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

}
