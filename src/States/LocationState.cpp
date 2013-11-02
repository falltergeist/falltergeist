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

// Falltergeist includes
#include "../Engine/Animation.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/LocationObject.h"
#include "../States/LocationState.h"
#include "../Engine/Mouse.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState() : State()
{
    _hexCursor = new Surface(ResourceManager::surface("art/intrface/msef000.frm"));
    _hexCursor->setXOffset(- ceil(_hexCursor->width()/2));
    _hexCursor->setYOffset(- ceil(_hexCursor->height()/2));
}

LocationState::~LocationState()
{
    _game->setLocation(0);
    delete _hexCursor;
}

void LocationState::init()
{
    State::init();

    _location = new Location(_game->resourceManager()->mapFileType("maps/artemple.map"));
    _game->setLocation(_location);
    _background = new InteractiveSurface(_location->tilesBackground());
    _background->onLeftButtonClick((EventHandler) &LocationState::onBackgroundClick);
    _background->onKeyboardRelease((EventHandler) &LocationState::onKeyboardRelease);

    add(_background);
    add(_hexCursor);
}

void LocationState::onBackgroundClick(Event * event)
{
    int x = _location->camera()->x() + event->x();
    int y = _location->camera()->y() + event->y();
    unsigned int hexagon = _location->positionToHexagon(x, y);

    std::cout << x << " : " << y << " > " << hexagon << std::endl;
}

void LocationState::onKeyboardRelease(Event * event)
{
    if (event->keyCode() == SDLK_g) // "g" button - enable\disable hex grid
    {
        if (_hexagonalGrid)
        {
            _hexagonalGrid = false;
        }
        else
        {
            _hexagonalGrid = true;
        }
    }
}

void LocationState::blit()
{

    State::blit();

    if (_location == 0) return;

    _drawHexagonalGrid();

    _hexCursor->blit(_game->screen()->surface());

    for (std::vector<LocationObject *>::iterator it = _location->objectsToRender()->begin(); it != _location->objectsToRender()->end(); ++it)
    {
        LocationObject * object = *it;

        int oldX = object->x();
        int oldY = object->y();
        int newX = oldX - _location->camera()->x();
        int newY = oldY - _location->camera()->y();

        object->setX(newX);
        object->setY(newY);
        object->blit(_game->screen()->surface());
        object->setX(oldX);
        object->setY(oldY);

    }
}

void LocationState::_drawHexagonalGrid()
{
    if (!_hexagonalGrid) return;
    Surface * hexagon = ResourceManager::surface("art/intrface/msef000.frm");
    hexagon->setXOffset(0 - hexagon->width()/2);
    hexagon->setYOffset(0 - hexagon->height()/2);
    for (unsigned int i = 0; i != 200*200; ++i)
    {
        int x = _location->hexagonToX(i) - _location->camera()->x();
        int y = _location->hexagonToY(i) - _location->camera()->y();
        hexagon->setX(x);
        hexagon->setY(y);
        hexagon->blit(_game->screen()->surface());
    }
}

void LocationState::think()
{

    if (!_location) return;
    _location->think();

    int x = _location->camera()->x() + _game->mouse()->x();
    int y = _location->camera()->y() + _game->mouse()->y();
    unsigned int hexagon = _location->positionToHexagon(x, y);

    _hexCursor->setX(_location->hexagonToX(hexagon) - _location->camera()->x());
    _hexCursor->setY(_location->hexagonToY(hexagon) - _location->camera()->y());

    if (SDL_GetTicks() >= _scrollTicks + 10)
    {
        bool moved;
        _scrollTicks = SDL_GetTicks();
        if (_game->mouse()->cursorX() < 5) // LEFT
        {
            if (_game->mouse()->cursorY() < 5) //  LEFT-UP
            {
                moved = _location->scroll(true, false, true, false);
                if (moved)
                {
                    _game->mouse()->setType(Mouse::SCROLL_NW);
                }
                else
                {
                    _game->mouse()->setType(Mouse::SCROLL_NW_X);
                }
            }
            else if (_game->mouse()->cursorY() > 475) //LEFT-DOWN
            {
                moved = _location->scroll(false, true, true, false);
                if (moved)
                {
                    _game->mouse()->setType(Mouse::SCROLL_SW);
                }
                else
                {
                    _game->mouse()->setType(Mouse::SCROLL_SW_X);
                }
            }
            else
            {
                moved = _location->scroll(false, false, true, false);
                if (moved)
                {
                    _game->mouse()->setType(Mouse::SCROLL_W);
                }
                else
                {
                    _game->mouse()->setType(Mouse::SCROLL_W_X);
                }
            }
        }
        else if (_game->mouse()->cursorX() > 635) // RIGHT
        {
            if (_game->mouse()->cursorY() < 5) //  RIGHT-UP
            {
                moved = _location->scroll(true, false, false, true);
                if (moved)
                {
                    _game->mouse()->setType(Mouse::SCROLL_NE);
                }
                else
                {
                    _game->mouse()->setType(Mouse::SCROLL_NE_X);
                }
            }
            else if (_game->mouse()->cursorY() > 475) //RIGHT-DOWN
            {
                moved = _location->scroll(false, true, false, true);
                if (moved)
                {
                    _game->mouse()->setType(Mouse::SCROLL_SE);
                }
                else
                {
                    _game->mouse()->setType(Mouse::SCROLL_SE_X);
                }
            }
            else
            {
                moved = _location->scroll(false, false, false, true);
                if (moved)
                {
                    _game->mouse()->setType(Mouse::SCROLL_E);
                }
                else
                {
                    _game->mouse()->setType(Mouse::SCROLL_E_X);
                }
            }
        }
        else if (_game->mouse()->cursorY() < 5) // UP
        {
            moved = _location->scroll(true, false, false, false);
            if (moved)
            {
                _game->mouse()->setType(Mouse::SCROLL_N);
            }
            else
            {
                _game->mouse()->setType(Mouse::SCROLL_N_X);
            }
        }
        else if (_game->mouse()->cursorY() > 475) // DOWN
        {
            moved = _location->scroll(false, true, false, false);
            if (moved)
            {
                _game->mouse()->setType(Mouse::SCROLL_S);
            }
            else
            {
                _game->mouse()->setType(Mouse::SCROLL_S_X);
            }
        }
        else
        {
            _game->mouse()->setType(Mouse::BIG_ARROW);
        }

        if(moved)
        {
            _background->loadFromSurface(_location->tilesBackground());
        }
    }

}

}
