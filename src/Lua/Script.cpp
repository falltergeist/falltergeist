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
#include "../Lua/Console.h"
#include "../Lua/Module.h"
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
    if (luaL_loadfile(_lua_State, filename.c_str()))
    {
        std::string error = lua_tostring(_lua_State, -1);
        // pop error message from the stack
        lua_pop(_lua_State, 1);
        throw Exception("Lua::Script::Script() " + error);
    }

    addModule(std::shared_ptr<Module>(new Console));
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

void Script::addModule(std::shared_ptr<Module> module)
{
    _modules.push_back(module);
    module->attach(_lua_State);
}

Script::~Script()
{
    lua_close(_lua_State);
}

}
}
