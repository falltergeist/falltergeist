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
#include "../../Engine/Graphics/Renderer.h"
#include "../../Engine/Game.h"

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
    SDL_WarpMouseInWindow(Game::getInstance()->renderer()->window(),_x, _y);
}

void Mouse::setY(int y)
{
    _y = y;
    SDL_WarpMouseInWindow(Game::getInstance()->renderer()->window(),_x, _y);
}

void Mouse::setXY(int x, int y)
{
    _x = x;
    _y = y;
    SDL_WarpMouseInWindow(Game::getInstance()->renderer()->window(),_x, _y);
}

bool Mouse::visible()
{
    return _visible;
}

void Mouse::setVisible(bool value)
{
    _visible = value;
}

std::shared_ptr<ActiveUI> Mouse::ui()
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
    _ui.reset();
    switch(type)
    {
        case BIG_ARROW:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/stdarrow.frm"));
            break;
        case SCROLL_W:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrwest.frm"));
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case SCROLL_W_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrwx.frm"));
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case SCROLL_N:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrnorth.frm"));
            _ui->setXOffset( -_ui->width()*0.5);
            break;
        case SCROLL_N_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrnx.frm"));
            _ui->setXOffset( -_ui->width()*0.5);
            break;
        case SCROLL_S:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrsouth.frm"));
            _ui->setXOffset( -_ui->width()*0.5);
            _ui->setYOffset( -_ui->height());
            break;
        case SCROLL_S_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrsx.frm"));
            _ui->setXOffset(-_ui->width()*0.5);
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_E:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/screast.frm"));
            _ui->setXOffset( -_ui->width());
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case SCROLL_E_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/screx.frm"));
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height()*0.5);
            break;
        case SCROLL_NW:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrnwest.frm"));
            break;
        case SCROLL_NW_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrnwx.frm"));
            break;
        case SCROLL_SW:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrswest.frm"));
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_SW_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrswx.frm"));
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_NE:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrneast.frm"));
            _ui->setXOffset(-_ui->width());
            break;
        case SCROLL_NE_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrnex.frm"));
            _ui->setXOffset(-_ui->width());
            break;
        case SCROLL_SE:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrseast.frm"));
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_SE_X:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/scrsex.frm"));
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height());
            break;
        case HEXAGON_RED:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/msef000.frm"));
            //setXOffset(- width()/2);
            //setYOffset(- height()/2);
            //_lastType = _type;
            break;
        case ACTION:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/actarrow.frm"));
            break;
        case HAND:
            _ui = std::shared_ptr<Image>(new Image("art/intrface/hand.frm"));
            break;
        case WAIT:
            _ui = std::shared_ptr<Animation>(new Animation("art/intrface/wait.frm"));
            _ui->setXOffset(-_ui->width()*0.5);
            _ui->setYOffset(-_ui->height()*0.5);
            break;
        case NONE:
            break;
    }

    _type = type;
}

}
