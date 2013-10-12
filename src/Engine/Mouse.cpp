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

#include "../Engine/Mouse.h"
#include "../Engine/ResourceManager.h"
#include <iostream>
#include <cmath>

namespace Falltergeist
{

Mouse::Mouse() : InteractiveSurface()
{
    //loadFromSurface(ResourceManager::surface("art/intrface/actarrow.frm"));

    // Hide cursor
    SDL_ShowCursor(0);
    _cursorX = 320;
    _cursorY = 240;
    setCursor(BIG_ARROW);
}

void Mouse::think()
{
    SDL_GetMouseState(&_cursorX, &_cursorY);

}

Mouse::~Mouse()
{
    // Show cursor
    SDL_ShowCursor(1);
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

void Mouse::setCursor(unsigned int type)
{
    switch(type)
    {
        case BIG_ARROW:
            loadFromSurface(ResourceManager::surface("art/intrface/stdarrow.frm"));
            _x = 0; _y = 0;
            break;
        case SCROLL_W:
            loadFromSurface(ResourceManager::surface("art/intrface/scrwest.frm"));
            _x = 0; _y = - ceil(height()/2);
            break;
        case SCROLL_W_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrwx.frm"));
            _x = 0; _y = - ceil(height()/2);
            break;
        case SCROLL_N:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnorth.frm"));
            _x = - ceil(width()/2); _y = 0;
            break;
        case SCROLL_N_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnx.frm"));
            _x = - ceil(width()/2); _y = 0;
            break;
        case SCROLL_S:
            loadFromSurface(ResourceManager::surface("art/intrface/scrsouth.frm"));
            _x = - ceil(width()/2);  _y = - height();
            break;
        case SCROLL_S_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrsx.frm"));
            _x = - ceil(width()/2); _y = - height();
            break;
        case SCROLL_E:
            loadFromSurface(ResourceManager::surface("art/intrface/screast.frm"));
            _x = - width(); _y = - ceil(height()/2);
            break;
        case SCROLL_E_X:
            loadFromSurface(ResourceManager::surface("art/intrface/screx.frm"));
            _x = - width(); _y = - ceil(height()/2);
            break;
        case SCROLL_NW:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnwest.frm"));
            _x = 0; _y = 0;
            break;
        case SCROLL_NW_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnwx.frm"));
            _x = 0; _y = 0;
            break;
        case SCROLL_SW:
            loadFromSurface(ResourceManager::surface("art/intrface/scrswest.frm"));
            _x = 0; _y = - height();
            break;
        case SCROLL_SW_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrswx.frm"));
            _x = 0; _y = - height();
            break;

        case SCROLL_NE:
            loadFromSurface(ResourceManager::surface("art/intrface/scrneast.frm"));
            _x =  - width(); _y = 0;
            break;
        case SCROLL_NE_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrnex.frm"));
            _x =  - width(); _y = 0;
            break;
        case SCROLL_SE:
            loadFromSurface(ResourceManager::surface("art/intrface/scrseast.frm"));
            _x =  - width(); _y = - height();
            break;
        case SCROLL_SE_X:
            loadFromSurface(ResourceManager::surface("art/intrface/scrsex.frm"));
            _x =  - width(); _y = - height();
            break;
        case HEXAGON_RED:
            loadFromSurface(ResourceManager::surface("art/intrface/msef000.frm"));
            _x =  - ceil(width()/2); _y = - ceil(height()/2);
            break;


    }
}

}
