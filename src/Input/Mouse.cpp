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
#include "../Game/Game.h"
#include "../Graphics/AnimationQueue.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../UI/Image.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

Mouse::Mouse()
{
    // Hide cursor
    SDL_ShowCursor(0);
    // Trap mouse in window         - mouse warp doesn't work currently with this setting -- phobos2077
    /*if (!Game::getInstance()->settings()->fullscreen())
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }*/
}

Mouse::~Mouse()
{
    delete _ui;
    // Show cursor
    SDL_ShowCursor(1);
}

int Mouse::x() const
{
    return _x;
}

int Mouse::y() const
{
    return _y;
}

void Mouse::setX(int x)
{
    _x = x;
    auto renderer = Game::getInstance()->renderer();
    float scaleX = renderer->scaleX();
    float scaleY = renderer->scaleY();
    SDL_WarpMouseInWindow(renderer->sdlWindow(), _x*scaleX, _y*scaleY);
}

void Mouse::setY(int y)
{
    _y = y;
    auto renderer = Game::getInstance()->renderer();
    float scaleX = renderer->scaleX();
    float scaleY = renderer->scaleY();
    SDL_WarpMouseInWindow(renderer->sdlWindow(), _x*scaleX, _y*scaleY);
}

void Mouse::setState(Cursor state)
{
    _states.clear();
    pushState(state);
}

void Mouse::popState()
{
    if (_states.size() == 0) return;
    if (_states.size() == 1)
    {
        _setType(Cursor::NONE);
    }
    else
    {
        _setType(_states.at(_states.size() - 2));
    }
    _states.pop_back();
}

void Mouse::pushState(Cursor state)
{
    _setType(state);
    _states.push_back(state);
}

Mouse::Cursor Mouse::state() const
{
    if (_states.empty())
    {
        return Cursor::NONE;
    }
    return _states.back();
}

void Mouse::_setType(Cursor state)
{
    if (this->state() == state) return;
    delete _ui; _ui = 0;
    switch (state)
    {
        case Cursor::BIG_ARROW:
            _ui = new Image("art/intrface/stdarrow.frm");
            break;
        case Cursor::SCROLL_W:
            _ui = new Image("art/intrface/scrwest.frm");
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case Cursor::SCROLL_W_X:
            _ui = new Image("art/intrface/scrwx.frm");
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case Cursor::SCROLL_N:
            _ui = new Image("art/intrface/scrnorth.frm");
            _ui->setXOffset( -_ui->width()*0.5);
            break;
        case Cursor::SCROLL_N_X:
            _ui = new Image("art/intrface/scrnx.frm");
            _ui->setXOffset( -_ui->width()*0.5);
            break;
        case Cursor::SCROLL_S:
            _ui = new Image("art/intrface/scrsouth.frm");
            _ui->setXOffset( -_ui->width()*0.5);
            _ui->setYOffset( -_ui->height());
            break;
        case Cursor::SCROLL_S_X:
            _ui = new Image("art/intrface/scrsx.frm");
            _ui->setXOffset(-_ui->width()*0.5);
            _ui->setYOffset(-_ui->height());
            break;
        case Cursor::SCROLL_E:
            _ui = new Image("art/intrface/screast.frm");
            _ui->setXOffset( -_ui->width());
            _ui->setYOffset( -_ui->height()*0.5);
            break;
        case Cursor::SCROLL_E_X:
            _ui = new Image("art/intrface/screx.frm");
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height()*0.5);
            break;
        case Cursor::SCROLL_NW:
            _ui = new Image("art/intrface/scrnwest.frm");
            break;
        case Cursor::SCROLL_NW_X:
            _ui = new Image("art/intrface/scrnwx.frm");
            break;
        case Cursor::SCROLL_SW:
            _ui = new Image("art/intrface/scrswest.frm");
            _ui->setYOffset(-_ui->height());
            break;
        case Cursor::SCROLL_SW_X:
            _ui = new Image("art/intrface/scrswx.frm");
            _ui->setYOffset(-_ui->height());
            break;
        case Cursor::SCROLL_NE:
            _ui = new Image("art/intrface/scrneast.frm");
            _ui->setXOffset(-_ui->width());
            break;
        case Cursor::SCROLL_NE_X:
            _ui = new Image("art/intrface/scrnex.frm");
            _ui->setXOffset(-_ui->width());
            break;
        case Cursor::SCROLL_SE:
            _ui = new Image("art/intrface/scrseast.frm");
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height());
            break;
        case Cursor::SCROLL_SE_X:
            _ui = new Image("art/intrface/scrsex.frm");
            _ui->setXOffset(-_ui->width());
            _ui->setYOffset(-_ui->height());
            break;
        case Cursor::HEXAGON_RED:
            _ui = new Image("art/intrface/msef000.frm");
            _ui->setXOffset(- _ui->width()/2);
            _ui->setYOffset(- _ui->height()/2);
            break;
        case Cursor::ACTION:
            _ui = new Image("art/intrface/actarrow.frm");
            break;
        case Cursor::HAND:
            _ui = new Image("art/intrface/hand.frm");
            break;
        case Cursor::WAIT:
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
        case Cursor::NONE:
            break;
        default:
            break;
    }
}

void Mouse::render()
{
    if (state() == Cursor::NONE) return;

    if (!_ui) return;

    if (state() != Cursor::HEXAGON_RED)
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
        case Cursor::SCROLL_W:
        case Cursor::SCROLL_N:
        case Cursor::SCROLL_E:
        case Cursor::SCROLL_S:
        case Cursor::SCROLL_W_X:
        case Cursor::SCROLL_NW:
        case Cursor::SCROLL_NW_X:
        case Cursor::SCROLL_N_X:
        case Cursor::SCROLL_NE:
        case Cursor::SCROLL_NE_X:
        case Cursor::SCROLL_E_X:
        case Cursor::SCROLL_SE:
        case Cursor::SCROLL_SE_X:
        case Cursor::SCROLL_S_X:
        case Cursor::SCROLL_SW:
        case Cursor::SCROLL_SW_X:
            return true;
            break;
        default:
            return false;
    }
    return false;
}

UI* Mouse::ui()
{
    return _ui;
}

std::vector<Mouse::Cursor>* Mouse::states()
{
    return &_states;
}

unsigned Mouse::cursor() const
{
    return static_cast<unsigned>(state());
}

void Mouse::setCursor(unsigned value)
{
    if (value > static_cast<unsigned>(Cursor::HAND)) return;
    setState(static_cast<Cursor>(value));
}

}
