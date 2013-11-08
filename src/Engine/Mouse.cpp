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
#include "../Engine/Animation.h"
#include "../Engine/Game.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/Mouse.h"
#include "../Engine/ResourceManager.h"

// Third party includes

namespace Falltergeist
{

Mouse::Mouse() : InteractiveSurface()
{
    // Hide cursor
    SDL_ShowCursor(0);
    setType(BIG_ARROW);
}

Mouse::~Mouse()
{
    delete _animation;
    // Show cursor
    SDL_ShowCursor(1);
}

void Mouse::think()
{
    if (_animation) _animation->think();
    SDL_GetMouseState(&_cursorX, &_cursorY);

    auto game = &Game::getInstance();
    auto location = game->location();

    if (location && game->locationState())
    {
        //check if cursor in the scrolling area
        if (cursorX() < 5) // LEFT
        {
            if (cursorY() < 5) //  LEFT-UP
            {
                auto moved = location->scroll(true, false, true, false);
                setType( moved ? Mouse::SCROLL_NW : Mouse::SCROLL_NW_X);
            }
            else if (cursorY() > 475) //LEFT-DOWN
            {
                auto moved = location->scroll(false, true, true, false);
                setType(moved ? Mouse::SCROLL_SW : Mouse::SCROLL_SW_X);
            }
            else
            {
                auto moved = location->scroll(false, false, true, false);
                setType(moved ? Mouse::SCROLL_W : Mouse::SCROLL_W_X);
            }
        }
        else if (cursorX() > 635) // RIGHT
        {
            if (cursorY() < 5) //  RIGHT-UP
            {
                auto moved = location->scroll(true, false, false, true);
                setType(moved ? Mouse::SCROLL_NE : Mouse::SCROLL_NE_X);
            }
            else if (cursorY() > 475) //RIGHT-DOWN
            {
                auto moved = location->scroll(false, true, false, true);
                setType(moved ? Mouse::SCROLL_SE : Mouse::SCROLL_SE_X);
            }
            else
            {
                auto moved = location->scroll(false, false, false, true);
                setType(moved ? Mouse::SCROLL_E : Mouse::SCROLL_E_X);
            }
        }
        else if (cursorY() < 5) // UP
        {
            auto moved = location->scroll(true, false, false, false);
            setType(moved ? Mouse::SCROLL_N : Mouse::SCROLL_N_X);
        }
        else if (cursorY() > 475) // DOWN
        {
            auto moved = location->scroll(false, true, false, false);
            setType(moved ? Mouse::SCROLL_S : Mouse::SCROLL_S_X);
        }
        else if (_type != _lastType)
        {
            setType(_lastType);
        }

        switch (type())
        {
            case HEXAGON_RED:
                auto location = Game::getInstance().location();
                int x = location->camera()->x() + this->cursorX();
                int y = location->camera()->y() + this->cursorY();
                unsigned int hexagon = location->positionToHexagon(x, y);
                setCursorX(location->hexagonToX(hexagon) - location->camera()->x());
                setCursorY(location->hexagonToY(hexagon) - location->camera()->y());
                break;
        }
    }
}

int Mouse::cursorX()
{
    return _cursorX;
}

int Mouse::cursorY()
{
    return _cursorY;
}

void Mouse::setCursorX(int x)
{
    _cursorX = x;
}

void Mouse::setCursorY(int y)
{
    _cursorY = y;    
}

int Mouse::x()
{
    return _x + _cursorX;
}

int Mouse::y()
{
    return _y + _cursorY;
}

int Mouse::type()
{
    return _type;
}

void Mouse::setType(int type)
{
    delete _animation; _animation = 0;
    _type = type;
    switch(_type)
    {
        case BIG_ARROW:
            loadFromSurface(ResourceManager::surface("art/intrface/stdarrow.frm"));
            setXOffset(0);
            setYOffset(0);
            _lastType = _type;
            break;
        case SCROLL_W:
            loadFromSurface(ResourceManager::surface("art/intrface/scrwest.frm"));
            setYOffset( - ceil(height()/2));
            setXOffset(0);
            break;
        case SCROLL_W_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrwx.frm"));
            setYOffset( - ceil(height()/2));
            setXOffset(0);
            break;
        case SCROLL_N:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnorth.frm"));
            setXOffset( - ceil(width()/2));
            setYOffset(0);
            break;
        case SCROLL_N_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnx.frm"));
            setXOffset( - ceil(width()/2));
            setYOffset(0);
            break;
        case SCROLL_S:
            loadFromSurface(ResourceManager::surface("art/intrface/scrsouth.frm"));
            setXOffset( - ceil(width()/2));
            setYOffset( - height());
            break;
        case SCROLL_S_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrsx.frm"));
            setXOffset(- ceil(width()/2));
            setYOffset(- height());
            break;
        case SCROLL_E:
            loadFromSurface(ResourceManager::surface("art/intrface/screast.frm"));
            setXOffset( - width());
            setYOffset( - ceil(height()/2));
            break;
        case SCROLL_E_X:
            loadFromSurface(ResourceManager::surface("art/intrface/screx.frm"));
            setXOffset(- width());
            setYOffset(- ceil(height()/2));
            break;
        case SCROLL_NW:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnwest.frm"));
            setXOffset(0);
            setYOffset(0);
            break;
        case SCROLL_NW_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnwx.frm"));
            setXOffset(0);
            setYOffset(0);
            break;
        case SCROLL_SW:
            loadFromSurface(ResourceManager::surface("art/intrface/scrswest.frm"));
            setXOffset(0);
            setYOffset(- height());
            break;
        case SCROLL_SW_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrswx.frm"));
            setXOffset(0);
            setYOffset(- height());
            break;
        case SCROLL_NE:
            loadFromSurface(ResourceManager::surface("art/intrface/scrneast.frm"));
            setXOffset(- width());
            setYOffset(0);
            break;
        case SCROLL_NE_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnex.frm"));
            setXOffset(- width());
            setYOffset(0);
            break;
        case SCROLL_SE:
            loadFromSurface(ResourceManager::surface("art/intrface/scrseast.frm"));
            setXOffset(- width());
            setYOffset(- height());
            break;
        case SCROLL_SE_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrsex.frm"));
            setXOffset(- width());
            setYOffset(- height());
            break;
        case HEXAGON_RED:
            loadFromSurface(ResourceManager::surface("art/intrface/msef000.frm"));
            setXOffset(- width()/2);
            setYOffset(- height()/2);
            _lastType = _type;
            break;
        case ACTION:
            loadFromSurface(ResourceManager::surface("art/intrface/actarrow.frm"));
            setXOffset(0);
            setYOffset(0);
            _lastType = _type;
            break;
        case WAIT:
            _animation = new Animation("art/intrface/wait.frm");
            _animation->setEnabled(true);
            setXOffset(- width()/2);
            setYOffset(- height()/2);
            _lastType = _type;
            break;
        case NONE:
            loadFromSurface(new Surface());
            break;
    }
}

void Mouse::handle(Event* event)
{
    // use_on

    //x hexagon
    //x arrow
        //x лицо \/ x стрелки поворота |/ x* рука
        //x* бинокль
        //x* рюкзак
        //x* голова
        //x* отмена

    //* aim
}

SDL_Surface* Mouse::sdl_surface()
{
    if (_animation) return _animation->surface()->sdl_surface();
    return InteractiveSurface::sdl_surface();
}

}
