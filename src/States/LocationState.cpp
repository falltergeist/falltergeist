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

#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Location.h"
#include "../Engine/LocationObject.h"
#include "../UI/TextArea.h"
#include "../Engine/Mouse.h"
#include "../Engine/Animation.h"
#include <cmath>

namespace Falltergeist
{

LocationState::LocationState(Game * game) : State(game)
{
    _scrollTicks = 0;
    _location = 0;
    _background = 0;
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    State::init();

    _location = new Location(_game->resourceManager()->mapFileType("maps/broken1.map"));
    _background = new Surface(_location->tilesBackground());
    add(_background);
}

void LocationState::blit()
{
    State::blit();

    if (_location == 0) return;

    for (std::vector<LocationObject *>::iterator it = _location->objects()->begin(); it != _location->objects()->end(); ++it)
    {
        LocationObject * object = *it;
        if (!object->visible()) continue;

        int oldX = object->x();
        int oldY = object->y();
        int newX = oldX - _location->cameraX() + 320;
        int newY = oldY - _location->cameraY() + 240;

        object->setX(newX);
        object->setY(newY);
        object->blit(_game->screen()->surface());
        object->setX(oldX);
        object->setY(oldY);
    }

}

void LocationState::think()
{
    if (!_location) return;
    _location->think();

    if (SDL_GetTicks() >= _scrollTicks + 1)
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
                    _game->mouse()->setCursor(Mouse::SCROLL_NW);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NW_X);
                }
            }
            else if (_game->mouse()->cursorY() > 475) //LEFT-DOWN
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
        else if (_game->mouse()->cursorX() > 635) // RIGHT
        {
            if (_game->mouse()->cursorY() < 5) //  RIGHT-UP
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
            else if (_game->mouse()->cursorY() > 475) //RIGHT-DOWN
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
        else if (_game->mouse()->cursorY() > 475) // DOWN
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
