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
#include "../Lua/Script.h"
#include "../State/LuaState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

LuaState::LuaState(const std::string& filename) : State()
{
    _script = new Lua::Script(filename);
    Event::export_to_lua_script(_script);
    LuaState::export_to_lua_script(_script);
    UI::export_to_lua_script(_script);
    ActiveUI::export_to_lua_script(_script);
    Image::export_to_lua_script(_script);
    ImageButton::export_to_lua_script(_script);
    _script->run();
}

LuaState::~LuaState()
{
    delete _script;
}

void LuaState::export_to_lua_script(Lua::Script* script)
{
    luabridge::getGlobalNamespace(script->luaState())
        .beginNamespace("game")
            .beginClass<LuaState>("State")
                .addProperty("x", &LuaState::x, &LuaState::setX)
                .addProperty("y", &LuaState::y, &LuaState::setY)
                .addProperty("fullscreen", &LuaState::fullscreen, &LuaState::setFullscreen)
                .addProperty("modal", &LuaState::modal, &LuaState::setModal)
                .addFunction("addUI", &LuaState::addUI)
            .endClass()
        .endNamespace();
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

void LuaState::handle(Event* event)
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

void LuaState::addUI(ActiveUI* ui)
{
    State::addUI(ui);
}

int LuaState::x() const
{
    return _x;
}

void LuaState::setX(int value)
{
    _x = value;
}

int LuaState::y() const
{
    return _y;
}

void LuaState::setY(int value)
{
    _y = value;
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
