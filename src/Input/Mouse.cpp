/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Related headers
#include "../Input/Mouse.h"

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{

namespace Input
{

Mouse::Mouse()
{
    SDL_ShowCursor(0); // Hide cursor
}

Mouse::~Mouse()
{
    SDL_ShowCursor(1); // Show cursor
}

int Mouse::x() const
{
    return _position.x();
}

int Mouse::y() const
{
    return _position.y();
}

void Mouse::setX(int x)
{
    setPosition({x, _position.y()});
}

void Mouse::setY(int y)
{
    setPosition({_position.x(), y});
}

const Point& Mouse::position() const
{
    return _position;
}

void Mouse::setPosition(const Point& pos)
{
    _position = pos;
    auto renderer = Game::getInstance()->renderer();
    float scaleX = renderer->scaleX();
    float scaleY = renderer->scaleY();
    SDL_WarpMouseInWindow(renderer->sdlWindow(), (int)(pos.x() * scaleX), (int)(pos.y() * scaleY));
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
    _ui.reset(nullptr);
    switch (state)
    {
        case Cursor::BIG_ARROW:
            _ui = std::make_unique<UI::Image>("art/intrface/stdarrow.frm");
            break;
        case Cursor::SCROLL_W:
            _ui = std::make_unique<UI::Image>("art/intrface/scrwest.frm");
            _ui->setOffset(0, -_ui->size().height() / 2);
            break;
        case Cursor::SCROLL_W_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrwx.frm");
            _ui->setOffset(0, -_ui->size().height() / 2);
            break;
        case Cursor::SCROLL_N:
            _ui = std::make_unique<UI::Image>("art/intrface/scrnorth.frm");
            _ui->setOffset( -_ui->size().width() / 2, 0);
            break;
        case Cursor::SCROLL_N_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrnx.frm");
            _ui->setOffset( -_ui->size().width() / 2, 0);
            break;
        case Cursor::SCROLL_S:
            _ui = std::make_unique<UI::Image>("art/intrface/scrsouth.frm");
            _ui->setOffset( -_ui->size().width() / 2, -_ui->size().height());
            break;
        case Cursor::SCROLL_S_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrsx.frm");
            _ui->setOffset(-_ui->size().width() / 2, -_ui->size().height());
            break;
        case Cursor::SCROLL_E:
            _ui = std::make_unique<UI::Image>("art/intrface/screast.frm");
            _ui->setOffset( -_ui->size().width(), -_ui->size().height() / 2);
            break;
        case Cursor::SCROLL_E_X:
            _ui = std::make_unique<UI::Image>("art/intrface/screx.frm");
            _ui->setOffset(-_ui->size().width(), -_ui->size().height() / 2);
            break;
        case Cursor::SCROLL_NW:
            _ui = std::make_unique<UI::Image>("art/intrface/scrnwest.frm");
            break;
        case Cursor::SCROLL_NW_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrnwx.frm");
            break;
        case Cursor::SCROLL_SW:
            _ui = std::make_unique<UI::Image>("art/intrface/scrswest.frm");
            _ui->setOffset(0, -_ui->size().height());
            break;
        case Cursor::SCROLL_SW_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrswx.frm");
            _ui->setOffset(0, -_ui->size().height());
            break;
        case Cursor::SCROLL_NE:
            _ui = std::make_unique<UI::Image>("art/intrface/scrneast.frm");
            _ui->setOffset(-_ui->size().width(), 0);
            break;
        case Cursor::SCROLL_NE_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrnex.frm");
            _ui->setOffset(-_ui->size().width(), 0);
            break;
        case Cursor::SCROLL_SE:
            _ui = std::make_unique<UI::Image>("art/intrface/scrseast.frm");
            _ui->setOffset(-_ui->size().width(), -_ui->size().height());
            break;
        case Cursor::SCROLL_SE_X:
            _ui = std::make_unique<UI::Image>("art/intrface/scrsex.frm");
            _ui->setOffset(-_ui->size().width(), -_ui->size().height());
            break;
        case Cursor::HEXAGON_RED:
            _ui = std::make_unique<UI::Image>("art/intrface/msef000.frm");
            _ui->setOffset(- _ui->size().width() / 2, - _ui->size().height() / 2);
            break;
        case Cursor::ACTION:
            _ui = std::make_unique<UI::Image>("art/intrface/actarrow.frm");
            break;
        case Cursor::HAND:
            _ui = std::make_unique<UI::Image>("art/intrface/hand.frm");
            break;
        case Cursor::SMALL_DOWN_ARROW:
            _ui = std::make_unique<UI::Image>("art/intrface/sdnarrow.frm");
            _ui->setOffset(-5, -10);
            break;
        case Cursor::SMALL_UP_ARROW:
            _ui = std::make_unique<UI::Image>("art/intrface/suparrow.frm");
            _ui->setOffset(-5, 0);
            break;
        case Cursor::WAIT:
        {
            auto queue = std::make_unique<UI::AnimationQueue>();
            queue->animations().push_back(std::make_unique<UI::Animation>("art/intrface/wait.frm"));
            queue->setRepeat(true);
            queue->start();
            _ui = std::move(queue);
            _ui->setOffset(Point() - _ui->size() / 2);
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

    if (_ui)
    {
        if (state() != Cursor::HEXAGON_RED)
        {
            _ui->setPosition(position());
        }
        _ui->render();
    }
}

void Mouse::think()
{
    SDL_GetMouseState(&_position.rx(), &_position.ry());
    _position = Point(
        static_cast<int>(_position.x() / Game::getInstance()->renderer()->scaleX()),
        static_cast<int>(_position.y() / Game::getInstance()->renderer()->scaleY())
    );
    if (_ui)
    {
        _ui->think();
    }
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
        default:
            return false;
    }
}

UI::Base* Mouse::ui()
{
    return _ui.get();
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

void Mouse::renderOutline()
{
    if (state() == Cursor::NONE) return;

    if (_ui)
    {
        if (state() != Cursor::HEXAGON_RED)
        {
            _ui->setPosition(position());
        }
        _ui->setOutline(1);
        _ui->render();
        _ui->setOutline(0);
    }
}
}
}
