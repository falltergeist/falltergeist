#include "../Engine/Location.h"
#include "../Engine/LocationObject.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
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

        if (mapObject->objectTypeId() == 1) continue; // SKIP critters for now
        if (mapObject->objectTypeId() == 5) continue; // SKIP critters for now

        unsigned int FID = (mapObject->frmTypeId() << 24) | mapObject->frmId();
        libfalltergeist::FrmFileType * frm = ResourceManager::frmFileType(FID);
        if (frm == 0)
        {
            std::cout << "FRM == 0 :( " << std::endl;
            continue;
        }
        LocationObject * locationObject = new LocationObject();
        locationObject->loadFromSurface(new Surface(frm, 0, 0));



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
