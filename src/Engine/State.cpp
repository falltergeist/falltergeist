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
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/State.h"
#include "../Engine/Surface.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ActiveUI.h"
#include "../Engine/UI.h"

// Third party includes

namespace Falltergeist
{

State::State() : EventReciever()
{
    _game = &Game::getInstance();
}

State::~State()
{

    while (!_ui.empty())
    {
        delete _ui.back();
        _ui.pop_back();
    }

}

void State::init()
{
    _initialized = true;
}

void State::think()
{
    for (std::vector<Surface*>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        (*i)->think();
    }
}

void State::blit()
{
    for (std::vector<Surface*>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        (*i)->blit(_game->screen()->surface());
    }
}

bool State::initialized()
{
    return _initialized;
}

bool State::fullscreen()
{
    return _fullscreen;
}

void State::setFullscreen(bool value)
{
    _fullscreen = value;
}

bool State::scrollable()
{
    return _scrollable;
}

void State::setScrollable(bool value)
{
    _scrollable = value;
}

void State::add(Surface* surface)
{
    _surfaces.push_back(surface);
}

void State::add(UI* ui)
{
    _ui.push_back(ui);
}

void State::add(ActiveUI* activeUi)
{
    _activeUi.push_back(activeUi);
    add((UI*)activeUi);
}

void State::add(std::vector<Surface*> surfaces)
{
    for (auto& surface : surfaces) _surfaces.push_back(surface);
}

void State::handle(Event* event)
{
    for (std::vector<ActiveUI*>::reverse_iterator i = _activeUi.rbegin(); i < _activeUi.rend(); i++)
    {
        (*i)->handle(event);
    }
}

std::vector<UI*>* State::ui()
{
    return &_ui;
}


}
