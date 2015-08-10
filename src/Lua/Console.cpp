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
#include "../Logger.h"
#include "../Lua/Console.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

using namespace luabridge;

Console::Console()
{
}

Console::~Console()
{
}

void Console::attach(lua_State* L)
{
    getGlobalNamespace(L).
        beginNamespace("console")
            .addFunction("debug", debug)
            .addFunction("info", info)
            .addFunction("warning", warning)
            .addFunction("error", error)
            .addFunction("critical", critical)
        .endNamespace();
}

int Console::debug(lua_State* L)
{
    const char* str = lua_tostring(L, 1);
    Logger::debug() << str << std::endl;
    return 0;
}

int Console::info(lua_State* L)
{
    const char* str = lua_tostring(L, 1);
    Logger::info() << str << std::endl;
    return 0;
}

int Console::warning(lua_State* L)
{
    const char* str = lua_tostring(L, 1);
    Logger::warning() << str << std::endl;
    return 0;
}

int Console::error(lua_State* L)
{
    const char* str = lua_tostring(L, 1);
    Logger::error() << str << std::endl;
    return 0;
}

int Console::critical(lua_State* L)
{
    const char* str = lua_tostring(L, 1);
    Logger::critical() << str << std::endl;
    return 0;
}

}
}
