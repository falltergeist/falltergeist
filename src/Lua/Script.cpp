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
#include "../Exception.h"
#include "../functions.h"
#include "../Lua/Script.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

using namespace luabridge;

Script::Script(const std::string& filename)
{
    _filename = filename;
    _lua_State = lua_open();

    luaL_openlibs(_lua_State);

    luabridge::getGlobalNamespace(_lua_State)
        .beginNamespace("game")
            .addFunction("translate", translate)
        .endNamespace();

    if (luaL_loadfile(_lua_State, filename.c_str()))
    {
        std::string error = lua_tostring(_lua_State, -1);
        // pop error message from the stack
        lua_pop(_lua_State, 1);
        throw Exception("Lua::Script::Script() " + error);
    }

}

void Script::run()
{
    int result = lua_pcall(_lua_State, 0, 0, 0);

    if (result)
    {
        std::string error = lua_tostring(_lua_State, -1);
        // pop error message from the stack
        lua_pop(_lua_State, 1);
        throw Exception("Lua::Script::run() " + error);
    }
}

Script::~Script()
{
    lua_close(_lua_State);
}

bool Script::get(const std::string& name, bool defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (lua_isnil(_lua_State, -1))
    {
        return defaultValue;
    }

    return lua_toboolean(_lua_State, -1);
}

int Script::get(const std::string& name, int defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (!lua_isnumber(_lua_State, -1))
    {
        return defaultValue;
    }
    return lua_tointeger(_lua_State, -1);
}

double Script::get(const std::string& name, double defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (!lua_isnumber(_lua_State, -1))
    {
        return defaultValue;
    }
    return lua_tonumber(_lua_State, -1);
}

std::string Script::get(const std::string& name, const std::string& defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (!lua_isstring(_lua_State, -1))
    {
        return defaultValue;
    }
    return lua_tostring(_lua_State, -1);
}

lua_State* Script::luaState()
{
    return _lua_State;
}

}
}
