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

#include "../Engine/Location.h"
#include "../Engine/LocationObject.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/Animation.h"
#include <cmath>
#include <iostream>

namespace Falltergeist
{

Location::Location(libfalltergeist::MapFileType * mapFile)
{
    _cols = 100;
    _rows = 100;
    _mapFile = mapFile;
    _tilesLst = ResourceManager::lstFileType("art/tiles/tiles.lst");
    _tilesBackground = new Surface(640, 480);
    _tilesBackground->fill(0xFF000000);
    _objects = new std::vector<LocationObject *>;
    init();
}

Location::~Location()
{
    delete _tilesLst;
    //delete _tilesBackground;
    delete _objects;
}

void Location::init()
{
    // Инициализируем положение камеры
    unsigned int defaultPosition = _mapFile->defaultPosition();
    _cameraX = hexagonToX(defaultPosition);
    _cameraY = hexagonToY(defaultPosition);

    _elevation = _mapFile->defaultElevation();

    std::list<libfalltergeist::MapObject *> * mapObjects = _mapFile->elevations()->at(_elevation)->objects();

    for (std::list<libfalltergeist::MapObject *>::iterator it = mapObjects->begin(); it != mapObjects->end(); ++it)
    {
        libfalltergeist::MapObject * mapObject = *it;

        LocationObject * locationObject = new LocationObject();
        locationObject->setObjectId(mapObject->objectId());
        locationObject->setObjectTypeId(mapObject->objectTypeId());

        unsigned int PID = (mapObject->objectTypeId() << 24) | mapObject->objectId();
        locationObject->setDescriptionId(ResourceManager::proFileType(PID)->messageId());

        if (mapObject->objectTypeId() == 1)
        {
            std::cout << std::dec << locationObject->objectTypeId() << " - " << locationObject->descriptionId() << " : ";
            std::cout << locationObject->name() << " | " << locationObject->description() << std::endl;
            continue; // SKIP critters for now
        }
        if (mapObject->objectTypeId() == 5)
        {
        }

        unsigned int FID = (mapObject->frmTypeId() << 24) | mapObject->frmId();
        libfalltergeist::FrmFileType * frm = ResourceManager::frmFileType(FID);

        //if (frm == 0) std::cout << mapObject->objectTypeId() << " - " << mapObject->objectId() << " NO FRM" << std::endl;

        if (mapObject->objectTypeId() == 5)
        {
            if (mapObject->objectId() == 12) // какая то хрень выстроенная форму прямоугольника
            {
                frm = ResourceManager::frmFileType("art/intrface/msef000.frm");
            }
            else if (mapObject->objectId() == 16) // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 17) // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 18) // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 19) // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 20) // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 23)  // exit to temple
            {
                frm = ResourceManager::frmFileType("art/intrface/msef002.frm");
            }
            else
            {
                std::cout << std::dec << locationObject->objectTypeId() << " - " << locationObject->objectId() << " - " << locationObject->descriptionId() << " : ";
                std::cout << locationObject->name() << " | " << locationObject->description() << std::endl;
                //continue; // SKIP MISC for now
            }
        }

        if (frm == 0)
        {
            std::cout << "FRM == 0 :( " << std::endl;
            delete locationObject;
            continue;
        }

        if (frm->framesPerDirection() > 1)
        {
            locationObject->setAnimation(new Animation(frm));
        }
        else
        {
            locationObject->loadFromSurface(new Surface(frm));
        }


        //if (frm->framesPerDirection() > 1)
        //{
            //std::cout << "ANIMATION" << std::endl;
        //}
        //locationObject->loadFromSurface()

        /*
        switch (mapObject->objectTypeId())
        {
            case libfalltergeist::ProFileType::TYPE_ITEM:
                break;
            case libfalltergeist::ProFileType::TYPE_CRITTER:
                break;
            case libfalltergeist::ProFileType::TYPE_SCENERY:

                break;
            case libfalltergeist::ProFileType::TYPE_TILE:
                break;
            case libfalltergeist::ProFileType::TYPE_WALL:
                break;
            case libfalltergeist::ProFileType::TYPE_MISC:
                break;
        }
        */
        int locX = locationObject->x() + hexagonToX(mapObject->hexPosition()) - (locationObject->width() - floor(locationObject->width()/2));
        int locY = locationObject->y() + hexagonToY(mapObject->hexPosition()) - locationObject->height();

        locationObject->x(locX);
        locationObject->y(locY);

        _objects->push_back(locationObject);
    }

    generateBackground();
}

void Location::think()
{
    for (std::vector<LocationObject *>::iterator it = _objects->begin(); it != _objects->end(); ++it)
    {
        LocationObject * object = *it;
        object->think();
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
        if (tileX + TILE_WIDTH < _cameraX - 320) continue;
        if (tileX > _cameraX + 320) continue;
        if (tileY + TILE_HEIGHT < _cameraY - 240) continue;
        if (tileY > _cameraY + 240) continue;


        std::string frmName = _tilesLst->strings()->at(_mapFile->elevations()->at(_elevation)->floorTiles[i]);
        Surface * tile = ResourceManager::surface("art/tiles/" + frmName);

        tile->x(tileX - _cameraX + 320);
        tile->y(tileY - _cameraY + 240);
        tile->blit(_tilesBackground);
    }
}

int Location::hexagonToX(unsigned int hexagon)
{
    unsigned int a = hexagon % 200;
    unsigned int b = ceil(hexagon/200);
    hexagon = a*200 + b;

    unsigned int y = ceil(hexagon/200);
    int centerX = 48*(_cols-1) + 48 + 16*(hexagon%200) - 24*y;

        if (((unsigned int)ceil(hexagon/200))%2 == 1)
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

        if (((unsigned int)ceil(hexagon/200))%2 == 1)
        {
            centerY -= 6;
        }
    return centerY + 12;

}

libfalltergeist::MapFileType * Location::mapFile()
{
    return _mapFile;
}

int Location::tileToX(unsigned int tile)
{
    return (_cols - tile % _cols - 1)*48 + 32*ceil(tile / _cols);
}

int Location::tileToY(unsigned int tile)
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

    if (up)
    {
        if (_cameraY >= 3 + 240)
        {
            _cameraY -= 3;
            changed = true;
        }
    }
    if (left)
    {
        if (_cameraX >= 3 + 320)
        {
            _cameraX -= 3;
            changed = true;
        }
    }
    if (down)
    {

        if (_cameraY < height() - 3 - 240)
        {
            _cameraY += 3;
            changed = true;
        }
    }
    if (right)
    {
        if (_cameraX < width() - 3 - 320)
        {
            _cameraX += 3;
            changed = true;
        }
    }


    if (changed)
    {
        generateBackground();
    }
    return changed;
}

std::vector<LocationObject *> * Location::objects()
{
    return _objects;
}

unsigned int Location::width()
{
    return 48*_cols + 32*_rows;
}

unsigned int Location::height()
{
    return 12*_cols + 24*_rows;
}

unsigned int Location::cameraX()
{
    return _cameraX;
}

unsigned int Location::cameraY()
{
    return _cameraY;
}

}
