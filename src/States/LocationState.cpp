#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Location.h"
#include <cmath>

namespace Falltergeist
{

LocationState::LocationState(Game * game) : State(game)
{
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    State::init();
    Location * location = new Location(100, 100);
    libfalltergeist::MapFileType * map = _game->resourceManager()->mapFileType("maps/artemple.map");
    libfalltergeist::LstFileType * lst = _game->resourceManager()->lstFileType("art/tiles/tiles.lst");

    Surface * hexagon = _game->resourceManager()->surface("art/intrface/msef000.frm"); // 001 - solid green  002 - solid red
    Surface * player  = _game->resourceManager()->surface("art/intrface/msef001.frm");

    unsigned int cols = 100;
    unsigned int rows = 100;
    unsigned int width = 48*cols + 32*rows; // 80*100 ??
    unsigned int height = 12*cols + 24*rows;// 36*100 ??

    _cameraX = 3750; //3750
    _cameraY = 1300;
    _direction = 0; //left

    _elevation = new Surface(width, height);
    _elevation->fill(0xFF000000);
    for (unsigned int y = 0; y != rows; ++y)
    {
        for (unsigned int x = 0; x != cols; ++x)
        {
            unsigned int i = cols * x + y;

            std::string frmName = lst->strings()->at(map->elevations()->at(0)->floorTiles[i]);
            Surface * tile = _game->resourceManager()->surface("art/tiles/" + frmName);

            unsigned int tileX = (cols - y - 1)*48 + 32*x;
            unsigned int tileY = x*24 + y*12;

            //if (tileX >= _cameraX - 80 && tileX <= _cameraX + 640)
            {
                //if (tileY >= _cameraY - 32 && tileY <= _cameraY + 480)
                {
                    tile->x(tileX);
                    tile->y(tileY);
                    tile->blit(_elevation);
                }
            }
        }
    }

    for (unsigned int i = 0; i != 200*200; i++)
    {
        unsigned int centerX = location->hexagonToX(i);
        unsigned int centerY = location->hexagonToY(i);

        hexagon->x(centerX - 16 + 16);
        hexagon->y(centerY - 8 + 8);
        hexagon->copyTo(_elevation);
    }

    /*
    std::list<libfalltergeist::MapObject *>::iterator it;
    std::list<libfalltergeist::MapObject *> * objects;
    objects = map->elevations()->at(0)->objects();
    for (it = objects->begin(); it !=  objects->end(); ++it)
    {
        unsigned int frmTypeId = (*it)->frmTypeId();
        unsigned int frmId = (*it)->frmId();
        unsigned int FID = (frmTypeId << 24) | frmId;

        if ((*it)->objectTypeId() == 5) continue;

        Surface * obj = _game->resourceManager()->surface(FID);
        if (obj == 0) continue;

        int hexPosition = (*it)->hexPosition();
        if (hexPosition < 0) continue;

        obj->x(location->hexagonToX(hexPosition));
        obj->y(location->hexagonToY(hexPosition));
        obj->copyTo(_elevation);

    }
    */
    player->x(location->hexagonToX(map->defaultPosition()));
    player->y(location->hexagonToY(map->defaultPosition()));
    player->copyTo(_elevation);

    //_camera = _elevation->crop(_cameraX, _cameraY, 640, 480);
    add(_elevation);
    _elevation->x(-_cameraX);
    _elevation->y(-_cameraY);


    SDL_SaveBMP(_elevation->sdl_surface(), "elevation2.bmp");



}

void LocationState::think()
{
    return;
    unsigned int radius = 200;

    if (_lastTicks + 20 < SDL_GetTicks())
    {
        _lastTicks = SDL_GetTicks();

        switch(_direction)
        {
            case 0: //left
                if (_cameraX > 3750 - radius)
                {
                    _cameraX -= 1;
                }
                else
                {
                    _direction = 1;
                }

                break;
            case 1: //up
                if (_cameraY > 1300 - radius)
                {
                    _cameraY -= 1;
                }
                else
                {
                    _direction = 2;
                }
                break;
            case 2: //right
                if (_cameraX < 3750 + radius)
                {
                    _cameraX += 1;
                }
                else
                {
                    _direction = 3;
                }
                break;
            case 3: //down
                if (_cameraY < 1300 + radius)
                {
                    _cameraY += 1;
                }
                else
                {
                    _direction = 0;
                }
                break;
        }


        _elevation->x(-_cameraX);
        _elevation->y(-_cameraY);

        //delete _camera;
        //_camera->x(-10);
        //_camera = _elevation->crop(_cameraX, _cameraY, 640, 480);
    }
}

}
