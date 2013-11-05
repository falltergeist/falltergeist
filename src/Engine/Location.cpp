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
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Location::Location(libfalltergeist::MapFileType * mapFile)
{
    _cols = 100;
    _rows = 100;

    _objects = new std::vector<LocationObject *>;
    _objectsToRender = new std::vector<LocationObject *>;
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
    delete _objects;
    delete _objectsToRender;
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
        libfalltergeist::MapObject * mapObject = *it;

        auto object = new LocationObject();
        object->setPID(mapObject->PID());
        object->setFID(mapObject->FID());
        object->setOrientation(mapObject->orientation());
        object->setElevation(mapObject->elevation());

        if (mapObject->scriptId() > 0)
        {
            int sid = mapObject->scriptId();
            auto lst = ResourceManager::lstFileType("scripts/scripts.lst");
            std::cout << "sid: " << std::dec << sid << " of " << lst->strings()->size() << std::endl;
            auto filename = lst->strings()->at(sid);
            auto script = ResourceManager::intFileType(sid);
            if (script)
            {
                object->addScript(filename, new VM(script, object));
                object->script(filename)->initialize();
            }
        }
        if (mapObject->mapScriptId() > 0 && mapObject->mapScriptId() != mapObject->scriptId())
        {
            int sid = mapObject->mapScriptId();
            std::cout << "msid: " << sid << std::endl;
            auto lst = ResourceManager::lstFileType("scripts/scripts.lst");
            auto filename = lst->strings()->at(sid);
            auto script = ResourceManager::intFileType(sid);
            if (!script)
            {
                object->addScript(filename, new VM(script, object));
                object->script(filename)->initialize();
            }
        }
        auto proto = ResourceManager::proFileType(mapObject->PID());
        if (proto->scriptId() > 0)
        {
            int sid = proto->scriptId();
            std::cout << "psid: " << sid << std::endl;
            auto lst = ResourceManager::lstFileType("scripts/scripts.lst");
            auto filename = lst->strings()->at(sid);
            auto script = ResourceManager::intFileType(sid);
            if (!script)
            {
                object->addScript(filename, new VM(script, object));
                object->script(filename)->initialize();
            }
        }


        object->setDescriptionId(ResourceManager::proFileType(mapObject->PID())->messageId());

        object->setX(hexagonToX(mapObject->hexPosition()));
        object->setY(hexagonToY(mapObject->hexPosition()));

        _objects->push_back(object);
    }

    _player = new LocationObject();

    _player->setPID(0x01000040);
    _player->setFID(0x01000040);
    _player->setOrientation(_mapFile->defaultOrientation());
    _player->setX(hexagonToX(_mapFile->defaultPosition()));
    _player->setY(hexagonToY(_mapFile->defaultPosition()));
    _objects->push_back(_player);

    // ON MAP LOADED
    if (_mapFile->scriptId() > 0)
    {
        _locationScript = new VM(ResourceManager::intFileType(_mapFile->scriptId()-1), this);
        _locationScript->initialize();
    }

    // -----------------------

    _generateBackground();
    _checkObjectsToRender();
}

LocationObject* Location::player()
{
    return _player;
}

void Location::think()
{
    // ON MAP ENTERED
    if (!_initialized)
    {
        _initialized = true;
        if (_locationScript)
        {
            _locationScript->call("map_enter_p_proc");
        }


        for (auto it = _objects->begin(); it != _objects->end(); ++it)
        {
            LocationObject* object = *it;
            for (auto itt = object->scripts()->begin(); itt != object->scripts()->end(); ++itt)
            {
                VM* script = itt->second;
                std::cout << itt->first << std::endl;
                script->call("map_enter_p_proc");
                script->call("talk_p_proc");
            }
        }
    }
    else
    {

    }
    // -----------------

    for (std::vector<LocationObject *>::iterator it = _objects->begin(); it != _objects->end(); ++it)
    {
        LocationObject * object = *it;
        object->think();
    }
}


void Location::_checkObjectsToRender()
{
    _objectsToRender->clear();

    for (std::vector<LocationObject *>::iterator it = _objects->begin(); it != _objects->end(); ++it)
    {
        LocationObject * object = *it;

        // if object is out of camera borders
        if (object->x() + object->xOffset() + object->width() < camera()->x()) continue;
        if (object->y() + object->yOffset() + object->height() < camera()->y()) continue;

        if (object->x() + object->xOffset() > camera()->x() + camera()->width()) continue;
        if (object->y() + object->yOffset() > camera()->y() + camera()->height()) continue;

        if (object->animation())
        {
            //if (object->x()  - object->animation()->surfaces()->at(0)->width()/2 + object->animation()->xOffsetMin() > camera()->x() + camera()->width()) continue;
            if (object->x() + object->xOffset() > camera()->x() + camera()->width()) continue;
            if (object->y() + object->yOffset() > camera()->y() + camera()->height()) continue;
        }
        else
        {
            if (object->x() + object->xOffset() > camera()->x() + camera()->width()) continue;
            if (object->y() + object->yOffset() > camera()->y() + camera()->height()) continue;
        }


        _objectsToRender->push_back(object);
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

std::vector<LocationObject *> * Location::objects()
{
    return _objects;
}

std::vector<LocationObject *> * Location::objectsToRender()
{
    return _objectsToRender;
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
        throw Exception("Location::setMVAR(num, value) - num out of range: " + std::to_string(number));
    }
    _MVARS.at(number) = value;
}

int Location::MVAR(unsigned int number)
{
    if (number >= _MVARS.size())
    {
        throw Exception("Location::MVAR(num) - num out of range: " + std::to_string(number));
    }
    return _MVARS.at(number);
}

}
