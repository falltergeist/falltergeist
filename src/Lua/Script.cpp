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
#include "../Exception.h"
#include "../Lua/Script.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

Script::Script(std::string filename)
{
    _filename = filename;
    _lua_State = lua_open();
    luaL_openlibs(_lua_State);
    if (luaL_loadfile(_lua_State, filename.c_str()))
    {
        throw Exception("Lua::Script::Script() can't load file: " + _filename);
    }
}

void Script::run()
{
    int result = lua_pcall(_lua_State, 0, 0, 0);

    if (result)
    {
        throw Exception("Lua::Script::run() error happened in file: " + _filename);
    }
}

Script::~Script()
{
    lua_close(_lua_State);
}

}
}
