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

        libfalltergeist::FrmFileType * frm;

        if (mapObject->objectTypeId() == 1)
        {
            //std::cout << std::dec << locationObject->objectTypeId() << " - " << locationObject->descriptionId() << " : ";
            //std::cout << locationObject->name() << " | " << locationObject->description() << std::endl;
            //std::cout << "FrmId: " << mapObject->frmId() << std::endl;
            //std::cout << "FrmTypeId: " << mapObject->frmTypeId() << std::endl;
            //std::cout << "ID1: " << mapObject->objectID1() << std::endl;
            //std::cout << "ID2: " << mapObject->objectID2() << std::endl;
            //std::cout << "ID3: " << mapObject->objectID3() << std::endl;

            libfalltergeist::LstFileType * lst = ResourceManager::lstFileType("art/critters/critters.lst");
            std::string frmName = lst->strings()->at(mapObject->frmId());
            std::string frmBase = frmName.substr(0, 6);

            unsigned int ID1 = mapObject->objectID1();
            unsigned int ID2 = mapObject->objectID2();

            if (ID2 >= 0x26 && ID2 <= 0x2F)
            {
                if (ID1 >= 0x0B || ID1 == 0)
                {
                    std::cout << "Unsupported value" << std::endl;
                }
                else
                {
                    frmBase += ID1 + 0x63;
                    frmBase += ID2 + 0x3D;
                }
            }
            else if (ID2 == 0x24)
            {
                frmBase += "ch";
            }
            else if (ID2 == 0x25)
            {
                frmBase += "cj";
            }
            else if (ID2 == 0x40)
            {
                frmBase += "na";
            }
            else if (ID2 >= 0x30)
            {
                frmBase += "r";
                frmBase += ID2 + 0x31;
            }
            else if (ID2 >= 0x14)
            {
                frmBase += "b";
                frmBase += ID2 + 0x4d;
            }
            else if (ID2 == 0x12)
            {
                if (ID1 == 0x01)
                {
                    frmBase += "dm";
                }
                else if (ID1 == 0x04)
                {
                    frmBase += "gm";
                }
                else
                {
                    frmBase += "as";
                }
            }
            else if (ID2 == 0x0D)
            {
                if (ID1 > 0)
                {
                    frmBase += ID1 + 0x63;
                    frmBase += "e";
                }
                else
                {
                    frmBase += "an";
                }
            }
            else if (ID2 <= 0x01 && ID1 > 0)
            {
                frmBase += ID1 + 0x63;
                frmBase += ID2 + 0x61;
            }
            else
            {
                frmBase += "a";
                frmBase += ID2 + 0x61;
            }

            std::string extensions[] = {"frm", "frm0", "frm1", "frm2", "fr3", "frm4", "frm5", "frm6"};
            frmBase += "." + extensions[mapObject->objectID3()];

            //std::cout << frmBase << std::endl;


            frm = ResourceManager::frmFileType("art/critters/" + frmBase);
            //std::cout << "Frm: " << frm << std::endl;
        }
        else
        {
            unsigned int FID = (mapObject->frmTypeId() << 24) | mapObject->frmId();
            frm = ResourceManager::frmFileType(FID);
        }
        if (frm == 0) std::cout << mapObject->objectTypeId() << " - " << mapObject->objectId() << " NO FRM" << std::endl;


        if (mapObject->objectTypeId() == 5)
        {
            if (mapObject->objectId() == 12) // какая то хрень выстроенная форму прямоугольника
            {
                //frm = ResourceManager::frmFileType("art/intrface/msef000.frm");
                frm = 0;
                delete locationObject;
                continue;

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
            else if (mapObject->objectId() == 21)  // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 22)  // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else if (mapObject->objectId() == 23)  // exit to temple
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
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
            std::cout << "FRM == 0 TId: "<< locationObject->objectTypeId() << " ID: " << locationObject->objectId() << std::endl;
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

        locationObject->setX(hexagonToX(mapObject->hexPosition()));
        locationObject->setY(hexagonToY(mapObject->hexPosition()));

        _objects->push_back(locationObject);
    }

    LocationObject * player = new LocationObject();

    Animation * animation = new Animation(ResourceManager::frmFileType("art/critters/hanpwrga.frm"));

    player->setAnimation(animation);

    player->setX(hexagonToX(_mapFile->defaultPosition()));
    player->setY(hexagonToY(_mapFile->defaultPosition()));
    //add(animation);
    _objects->push_back(player);

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

        tile->setX(tileX - _cameraX + 320);
        tile->setY(tileY - _cameraY + 240);
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
        if (_cameraY >= 4 + 240)
        {
            _cameraY -= 4;
            changed = true;
        }
    }
    if (left)
    {
        if (_cameraX >= 4 + 320)
        {
            _cameraX -= 4;
            changed = true;
        }
    }
    if (down)
    {

        if (_cameraY < height() - 4 - 240)
        {
            _cameraY += 4;
            changed = true;
        }
    }
    if (right)
    {
        if (_cameraX < width() - 4 - 320)
        {
            _cameraX += 4;
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
