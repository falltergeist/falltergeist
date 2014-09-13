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
#include <iostream>

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
}

State::~State()
{
}

void State::init()
{
    _initialized = true;
}

void State::think()
{
    for (auto ui : _ui)
    {
        ui->think();
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

bool State::modal()
{
    return _modal;
}

void State::setModal(bool value)
{
    _modal = value;
}

void State::add(std::shared_ptr<UI> ui)
{
    _ui.push_back(ui);
}

void State::add(std::vector<std::shared_ptr<UI>> uis)
{
    for (auto ui : uis) add(ui);
}

void State::handle(std::shared_ptr<Event> event)
{
    for (auto it = _ui.rbegin(); it != _ui.rend(); ++it)
    {
        if (auto activeUI = std::dynamic_pointer_cast<ActiveUI>(*it))
        {
            if (event->handled()) continue;
            activeUI->handle(event);
        }
    }
}

std::vector<std::shared_ptr<UI>>* State::ui()
{
    return &_ui;
}


}
