#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Location.h"
#include "../UI/TextArea.h"
#include "../Engine/Mouse.h"
#include <cmath>

namespace Falltergeist
{

LocationState::LocationState(Game * game) : State(game)
{
    _scrollTicks = 0;
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    State::init();

    _location = new Location(_game->resourceManager()->mapFileType("maps/artemple.map"));

    //Surface * hexagon = _game->resourceManager()->surface("art/intrface/msef000.frm"); // 001 - solid green  002 - solid red
    //Surface * player  = _game->resourceManager()->surface("art/intrface/msef001.frm");

    _background = new Surface(_location->tilesBackground());
    add(_background);


    /*
    for (unsigned int i = 0; i != 200*200; i++)
    {
        unsigned int centerX = location->hexagonToX(i);
        unsigned int centerY = location->hexagonToY(i);

        hexagon->x(centerX - 16);
        hexagon->y(centerY - 8);

        hexagon->copyTo(_elevation);

        //TextArea * num = new TextArea("", centerX - 16, centerY - 8);
        //num->setText(i);
        //num->blit(_elevation);
        //delete num;
    }*/

    /*
    std::list<libfalltergeist::MapObject *>::iterator it;
    std::list<libfalltergeist::MapObject *> * objects;
    objects = map->elevations()->at(0)->objects();

    for (it = objects->begin(); it !=  objects->end(); ++it)
    {
        unsigned int frmTypeId = (*it)->frmTypeId();
        unsigned int frmId = (*it)->frmId();
        unsigned int FID = (frmTypeId << 24) | frmId;

        //if (FID != 0x2000563) continue; //fire pit

        unsigned int PID = ((*it)->objectTypeId() << 24) | (*it)->objectId();
        //std::cout << "PID: 0x" << std::hex << PID << std::endl;

        libfalltergeist::ProFileType * pro = _game->resourceManager()->getPrototype(PID);

        if (pro->frmOffset() != 0)
        {
            std::cout << "OFFSET: " << pro->frmOffset() <<  std::endl;
        }

        if ((*it)->objectTypeId() == 5) continue;

        Surface * obj = _game->resourceManager()->surface(FID, 0, (*it)->frameNumber());
        if (obj == 0)
        {
            //std::cout << "FID: " << FID << " : is null" << std::endl;
            continue;
        }

        int hexPosition = (*it)->hexPosition();
        if (hexPosition < 0) continue;

        libfalltergeist::FrmFileType * frm = _game->resourceManager()->frmFileType(FID);


        obj->x(frm->directions()->at(0)->shiftX() + location->hexagonToX(hexPosition) - (obj->width() - (int)floor(obj->width()/2)));
        obj->y(frm->directions()->at(0)->shiftY() + frm->directions()->at(0)->frames()->at(0)->offsetY() + location->hexagonToY(hexPosition) - obj->height());
        obj->blit(_elevation);

    }

    player->x(location->hexagonToX(map->defaultPosition()) - 16);
    player->y(location->hexagonToY(map->defaultPosition()) - 8);
    player->copyTo(_elevation);
    */
    //_camera = _elevation->crop(_cameraX, _cameraY, 640, 480);

    //_elevation->x(-_cameraX);
    //_elevation->y(-_cameraY);


    //SDL_SaveBMP(_elevation->sdl_surface(), "elevation2.bmp");



}

void LocationState::think()
{
    if (SDL_GetTicks() >= _scrollTicks + 1)
    {
        bool moved;
        _scrollTicks = SDL_GetTicks();
        if (_game->mouse()->cursorX() < 4) // LEFT
        {
            if (_game->mouse()->cursorY() < 4) //  LEFT-UP
            {
                moved = _location->scroll(true, false, true, false);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NW);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NW_X);
                }
            }
            else if (_game->mouse()->cursorY() > 476) //LEFT-DOWN
            {
                moved = _location->scroll(false, true, true, false);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SW);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SW_X);
                }
            }
            else
            {
                moved = _location->scroll(false, false, true, false);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_W);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_W_X);
                }
            }
        }
        else if (_game->mouse()->cursorX() > 636) // RIGHT
        {
            if (_game->mouse()->cursorY() < 4) //  RIGHT-UP
            {
                moved = _location->scroll(true, false, false, true);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NE);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NE_X);
                }
            }
            else if (_game->mouse()->cursorY() > 476) //RIGHT-DOWN
            {
                moved = _location->scroll(false, true, false, true);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SE);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SE_X);
                }
            }
            else
            {
                moved = _location->scroll(false, false, false, true);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_E);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_E_X);
                }
            }
        }
        else if (_game->mouse()->cursorY() < 5) // UP
        {
            moved = _location->scroll(true, false, false, false);
            if (moved)
            {
                _game->mouse()->setCursor(Mouse::SCROLL_N);
            }
            else
            {
                _game->mouse()->setCursor(Mouse::SCROLL_N_X);
            }
        }
        else if (_game->mouse()->cursorY() > 476) // DOWN
        {
            moved = _location->scroll(false, true, false, false);
            if (moved)
            {
                _game->mouse()->setCursor(Mouse::SCROLL_S);
            }
            else
            {
                _game->mouse()->setCursor(Mouse::SCROLL_S_X);
            }
        }
        else
        {
            _game->mouse()->setCursor(Mouse::BIG_ARROW);
        }

        if(moved)
        {
            _background->loadFromSurface(_location->tilesBackground());
        }
    }

}

}
