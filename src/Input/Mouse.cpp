/*
 * Copyright 2012-2015 Falltergeist Developers.
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
 */

// C++ standard includes

// Falltergeist includes
#include "../Input/Mouse.h"
#include "../Graphics/AnimationQueue.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Renderer.h"
#include "../Game/Game.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

Mouse::Mouse()
{
    // Hide cursor
    SDL_ShowCursor(0);
}

Mouse::~Mouse()
{
    delete _ui;
    // Show cursor
    SDL_ShowCursor(1);
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
    float scaleX = Game::getInstance()->renderer()->scaleX();
    float scaleY = Game::getInstance()->renderer()->scaleY();
    SDL_WarpMouseInWindow(Game::getInstance()->renderer()->window(),_x*scaleX, _y*scaleY);
}

void Mouse::setY(int y)
{
    _y = y;
    float scaleX = Game::getInstance()->renderer()->scaleX();
    float scaleY = Game::getInstance()->renderer()->scaleY();
    SDL_WarpMouseInWindow(Game::getInstance()->renderer()->window(),_x*scaleX, _y*scaleY);
}

void Mouse::setState(unsigned int state)
{
    _states.clear();
    pushState(state);
}

void Mouse::popState()
{
    if (_states.size() == 0) return;
    if (_states.size() == 1)
    {
        _setType(NONE);
    }
    else
    {
        _setType(_states.at(_states.size() - 2));
    }
    _states.pop_back();
}

void Mouse::pushState(unsigned int state)
{
    _setType(state);
    _states.push_back(state);
}

unsigned int Mouse::state()
{
    if (_states.empty()) return NONE;
    return _states.back();
}

void Mouse::_setType(unsigned int state)
{
    if (this->state() == state) return;
    delete _ui; _ui = 0;
    switch(state)
    {
        case BIG_ARROW:
            _ui = new Image("art/intrface/stdarrow.frm");
            break;
        case SCROLL_W:
            _ui = new Image("art/intrface/scrwest.frm");
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case SCROLL_W_X:
            _ui = new Image("art/intrface/scrwx.frm");
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case SCROLL_N:
            _ui = new Image("art/intrface/scrnorth.frm");
            _ui->setXOffset( -_ui->width()*0.5);
            break;
        case SCROLL_N_X:
            _ui = new Image("art/intrface/scrnx.frm");
            _ui->setXOffset( -_ui->width()*0.5);
            break;
        case SCROLL_S:
            _ui = new Image("art/intrface/scrsouth.frm");
            _ui->setXOffset( -_ui->width()*0.5);
            _ui->setYOffset( -_ui->height());
            break;
        case SCROLL_S_X:
            _ui = new Image("art/intrface/scrsx.frm");
            _ui->setXOffset(-_ui->width()*0.5);
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_E:
            _ui = new Image("art/intrface/screast.frm");
            _ui->setXOffset( -_ui->width());
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case SCROLL_E_X:
            _ui = new Image("art/intrface/screx.frm");
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height()*0.5);
            break;
        case SCROLL_NW:
            _ui = new Image("art/intrface/scrnwest.frm");
            break;
        case SCROLL_NW_X:
            _ui = new Image("art/intrface/scrnwx.frm");
            break;
        case SCROLL_SW:
            _ui = new Image("art/intrface/scrswest.frm");
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_SW_X:
            _ui = new Image("art/intrface/scrswx.frm");
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_NE:
            _ui = new Image("art/intrface/scrneast.frm");
            _ui->setXOffset(-_ui->width());
            break;
        case SCROLL_NE_X:
            _ui = new Image("art/intrface/scrnex.frm");
            _ui->setXOffset(-_ui->width());
            break;
        case SCROLL_SE:
            _ui = new Image("art/intrface/scrseast.frm");
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height());
            break;
        case SCROLL_SE_X:
            _ui = new Image("art/intrface/scrsex.frm");
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height());
            break;
        case HEXAGON_RED:
            _ui = new Image("art/intrface/msef000.frm");
            _ui->setXOffset(- _ui->width()/2);
            _ui->setYOffset(- _ui->height()/2);
            break;
        case ACTION:
            _ui = new Image("art/intrface/actarrow.frm");
            break;
        case HAND:
            _ui = new Image("art/intrface/hand.frm");
            break;
        case WAIT:
        {
            auto queue = new AnimationQueue();
            queue->animations()->push_back(new Animation("art/intrface/wait.frm"));
            queue->setRepeat(true);
            queue->start();
            _ui = queue;
            _ui->setXOffset(-_ui->width()*0.5);
            _ui->setYOffset(-_ui->height()*0.5);
            break;
        }
        case NONE:
            break;
    }
}

void Mouse::render()
{
    if (state() == NONE) return;

    if (!_ui) return;

    if (state() != HEXAGON_RED)
    {
        _ui->setX(_x);
        _ui->setY(_y);
    }
    _ui->render();
}

void Mouse::think()
{
    SDL_GetMouseState(&_x, &_y);
    _x=_x/Game::getInstance()->renderer()->scaleX();
    _y=_y/Game::getInstance()->renderer()->scaleY();
    if (_ui) _ui->think();
}

bool Mouse::scrollState()
{
    switch(this->state())
    {
        case SCROLL_W:
        case SCROLL_N:
        case SCROLL_E:
        case SCROLL_S:
        case SCROLL_W_X:
        case SCROLL_NW:
        case SCROLL_NW_X:
        case SCROLL_N_X:
        case SCROLL_NE:
        case SCROLL_NE_X:
        case SCROLL_E_X:
        case SCROLL_SE:
        case SCROLL_SE_X:
        case SCROLL_S_X:
        case SCROLL_SW:
        case SCROLL_SW_X:
            return true;
            break;
    }
    return false;
}

UI* Mouse::ui()
{
    return _ui;
}

std::vector<unsigned int>* Mouse::states()
{
    return &_states;
}

}
