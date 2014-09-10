/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include <iostream>

// Falltergeist includes
#include "../../Engine/Input/Mouse.h"
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/ResourceManager.h"
#include "../../UI/Image.h"
#include "../../Engine/Graphics/Animation.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

Mouse::Mouse()
{
    // Hide cursor
    SDL_ShowCursor(0);
    setType(BIG_ARROW);
}

Mouse::~Mouse()
{
    // Show cursor
    SDL_ShowCursor(1);
    delete _ui; _ui = 0;
}

void Mouse::think()
{
    SDL_GetMouseState(&_x, &_y);
    if (_ui) _ui->think();
}

int Mouse::x()
{
    return _x;
}

int Mouse::y()
{
    return _y;
}

void Mouse::setX(int x)
{
    _x = x;
    SDL_WarpMouse(_x, _y);
}

void Mouse::setY(int y)
{
    _y = y;
    SDL_WarpMouse(_x, _y);
}

bool Mouse::visible()
{
    return _visible;
}

void Mouse::setVisible(bool value)
{
    _visible = value;
}

ActiveUI* Mouse::ui()
{
    if (_ui)
    {
        _ui->setX(_x);
        _ui->setY(_y);
    }
    return _ui;
}

unsigned int Mouse::type()
{
    return _type;
}

void Mouse::setType(unsigned int type)
{
    if (_type == type) return;
    delete _ui; _ui = 0;
    switch(type)
    {
        case BIG_ARROW:
            _ui = new Image("art/intrface/stdarrow.frm");
            // 0 0
            break;
        case SCROLL_W:
            _ui = new Image("art/intrface/scrwest.frm");
            //setYOffset( - ceil(height()/2));
            //setXOffset(0);
            break;
        case SCROLL_W_X:
            _ui = new Image("art/intrface/scrwx.frm");
            //setYOffset( - ceil(height()/2));
            //setXOffset(0);
            break;
        case SCROLL_N:
            _ui = new Image("art/intrface/scrnorth.frm");
            //setXOffset( - ceil(width()/2));
            //setYOffset(0);
            break;
        case SCROLL_N_X:
            _ui = new Image("art/intrface/scrnx.frm");
            //setXOffset( - ceil(width()/2));
            //setYOffset(0);
            break;
        case SCROLL_S:
            _ui = new Image("art/intrface/scrsouth.frm");
            //setXOffset( - ceil(width()/2));
            //setYOffset( - height());
            break;
        case SCROLL_S_X:
            _ui = new Image("art/intrface/scrsx.frm");
            //setXOffset(- ceil(width()/2));
            //setYOffset(- height());
            break;
        case SCROLL_E:
            _ui = new Image("art/intrface/screast.frm");
            //setXOffset( - width());
            //setYOffset( - ceil(height()/2));
            break;
        case SCROLL_E_X:
            _ui = new Image("art/intrface/screx.frm");
            //setXOffset(- width());
            //setYOffset(- ceil(height()/2));
            break;
        case SCROLL_NW:
            _ui = new Image("art/intrface/scrnwest.frm");
            //setXOffset(0);
            //setYOffset(0);
            break;
        case SCROLL_NW_X:
            _ui = new Image("art/intrface/scrnwx.frm");
            //setXOffset(0);
            //setYOffset(0);
            break;
        case SCROLL_SW:
            _ui = new Image("art/intrface/scrswest.frm");
            //setXOffset(0);
            //setYOffset(- height());
            break;
        case SCROLL_SW_X:
            _ui = new Image("art/intrface/scrswx.frm");
            //setXOffset(0);
            //setYOffset(- height());
            break;
        case SCROLL_NE:
            _ui = new Image("art/intrface/scrneast.frm");
            //setXOffset(- width());"art/intrface/msef000.frm"
            //setYOffset(0);
            break;
        case SCROLL_NE_X:
            _ui = new Image("art/intrface/scrnex.frm");
            //setXOffset(- width());
            //setYOffset(0);
            break;
        case SCROLL_SE:
            _ui = new Image("art/intrface/scrseast.frm");
            //setXOffset(- width());
            //setYOffset(- height());
            break;
        case SCROLL_SE_X:
            _ui = new Image("art/intrface/scrsex.frm");
            //setXOffset(- width());
            //setYOffset(- height());
            break;
        case HEXAGON_RED:
            _ui = new Image("art/intrface/msef000.frm");
            //setXOffset(- width()/2);
            //setYOffset(- height()/2);
            //_lastType = _type;
            break;
        case ACTION:
            _ui = new Image("art/intrface/actarrow.frm");
            //setXOffset(0);
            //setYOffset(0);
            //_lastType = _type;
            break;
        case WAIT:
            _ui = new Animation("art/intrface/wait.frm");
            //_animation->setEnabled(true);
            //setXOffset(- width()/2);
            //setYOffset(- height()/2);
            //_lastType = _type;
            break;
        case NONE:
            //loadFromSurface(new Surface());
            break;
    }

    _type = type;
}

}
