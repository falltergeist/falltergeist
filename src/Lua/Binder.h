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

#ifndef FALLTERGEIST_LUA_BINDER_H
#define FALLTERGEIST_LUA_BINDER_H

// C++ standard includes

// Libfalltergeist includes

// Third party includes
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "LuaBridge.h"

namespace Falltergeist
{
namespace Lua
{

/**
 * Class for Luabridge bindings
 */
class Binder
{
public:
    Binder(lua_State* luaState);
    ~Binder();

    void bindAll();

private:
    lua_State* _luaState;
    luabridge::Namespace _gameNamespace();

    void _bindBasicClasses();
    void _bindUI();
    void _bindStates();

};

}
}

#endif //FALLTERGEIST_LUA_BINDER_H
