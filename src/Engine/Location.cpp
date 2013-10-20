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
    //delete _tilesBackground;
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

    _elevation = _mapFile->defaultElevation();

    std::vector<libfalltergeist::MapObject *> * mapObjects = _mapFile->elevations()->at(_elevation)->objects();

    for (std::vector<libfalltergeist::MapObject *>::iterator it = mapObjects->begin(); it != mapObjects->end(); ++it)
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
    player->loadFromSurface(ResourceManager::surface("art/intrface/msef000.frm"));
    player->setX(hexagonToX(_mapFile->defaultPosition()));
    player->setY(hexagonToY(_mapFile->defaultPosition()));
    //player->setXOffset(0);
    //player->setYOffset(player->height()/2);
    //add(animation);
    _objects->push_back(player);

    _generateBackground();
    _checkObjectsToRender();
}

void Location::think()
{
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
    unsigned int a = hexagon % 200;
    unsigned int b = ceil(hexagon/200);
    hexagon = a*200 + b;

    unsigned int y = ceil(hexagon/200);
    int centerX = 48*(_cols-1) + 48 + 16*(hexagon%200) - 24*y;

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

    unsigned int scrollDelta = 5;

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

unsigned int Location::width()
{
    return 48*_cols + 32*_rows;
}

unsigned int Location::height()
{
    return 12*_cols + 24*_rows;
}


}
