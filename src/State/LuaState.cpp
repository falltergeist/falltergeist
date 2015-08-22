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
#include "../Lua/Script.h"
#include "../State/LuaState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

LuaState::LuaState(const std::string& filename) : State()
{
    _script = new Lua::Script(filename);
    _script->run();
}

LuaState::~LuaState()
{
    delete _script;
}

void LuaState::init()
{
    if (_initialized) return;
    State::init();

    luabridge::LuaRef func = luabridge::getGlobal(_script->luaState(), "init");
    if (func.isFunction())
    {
        func(this);
    }
}

void LuaState::think()
{
    State::think();
    luabridge::LuaRef func = luabridge::getGlobal(_script->luaState(), "think");
    if (func.isFunction())
    {
        func(this);
    }
}

void LuaState::handle(Event::Event* event)
{
    luabridge::LuaRef func = luabridge::getGlobal(_script->luaState(), "handle");
    if (func.isFunction())
    {
        func(this, event);
    }
    State::handle(event);
}

void LuaState::render()
{
    State::render();
    luabridge::LuaRef func = luabridge::getGlobal(_script->luaState(), "render");
    if (func.isFunction())
    {
        func(this);
    }
}

void LuaState::addUI(UI::Base* ui)
{
    if (!ui) return;
    State::addUI(ui);
}

int LuaState::x() const
{
    return State::x();
}

void LuaState::setX(int value)
{
    State::setX(value);
}

int LuaState::y() const
{
    return State::y();
}

void LuaState::setY(int value)
{
    State::setY(value);
}

bool LuaState::fullscreen() const
{
    return _fullscreen;
}

void LuaState::setFullscreen(bool value)
{
    _fullscreen = value;
}

bool LuaState::modal() const
{
    return _modal;
}

void LuaState::setModal(bool value)
{
    _modal = value;
}

}
}
