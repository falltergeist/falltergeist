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
#include <iostream>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Lua/Inheritable.h"
#include "../State/LuaState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

LuaState::LuaState(luabridge::LuaRef table) : State(), _inheritable(table)
{
}

LuaState::~LuaState()
{
    // remove pointers, Lua will handle deleting the objects
    _ui.clear();
}

void LuaState::think()
{
    State::think();
    _inheritable.call("think");
}

void LuaState::handle(Event::Event* event)
{
    State::handle(event);
    _inheritable.call("handle", event);
}

void LuaState::render()
{
    State::render();
    _inheritable.call("render");
}

void LuaState::addUI(UI::Base* ui)
{
    if (!ui) return;
    State::addUI(ui);
}

void LuaState::onStateActivate(Event::State* event)
{
    _inheritable.call("onActivate", event);
}

void LuaState::onStateDeactivate(Event::State* event)
{
    _inheritable.call("onDeactivate", event);
}

void LuaState::onKeyDown(Event::Keyboard* event)
{
    _inheritable.call("onKeyDown", event);
}

}
}
