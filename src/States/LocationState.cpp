#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Location.h"

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

    libfalltergeist::MapFileType * map = _game->resourceManager()->mapFileType("maps/artemple.map");
    libfalltergeist::LstFileType * lst = _game->resourceManager()->lstFileType("art/tiles/tiles.lst");

    unsigned int cols = 100;
    unsigned int rows = 100;
    unsigned int width = 48*cols + 32*rows; // 80*100 ??
    unsigned int height = 12*cols + 24*rows;// 36*100 ??

    _cameraX = 3750;
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

    //_camera = _elevation->crop(_cameraX, _cameraY, 640, 480);
    add(_elevation);


    //SDL_SaveBMP(elevation->sdl_surface(), "elevation2.bmp");



}

void LocationState::think()
{
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
