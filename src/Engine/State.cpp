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
    for (std::vector<UI*>::iterator i = _ui.begin(); i < _ui.end(); i++)
    {
        (*i)->think();
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

void State::add(ActiveUI* activeUi)
{
    _activeUi.push_back(activeUi);
    add((UI*)activeUi);
}

void State::add(UI* ui)
{
    _ui.push_back(ui);
}

void State::add(std::vector<ActiveUI*> uis)
{
    for (auto& ui : uis) add(ui);
}

void State::add(std::vector<UI*> uis)
{
    for (auto& ui : uis) add(ui);
}

void State::handle(Event* event)
{
    for (auto it = _activeUi.rbegin(); it != _activeUi.rend(); ++it)
    {
        (*it)->handle(event);
    }
}

std::vector<UI*>* State::ui()
{
    return &_ui;
}


}
