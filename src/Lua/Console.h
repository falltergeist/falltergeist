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

#ifndef FALLTERGEIST_LUA_CONSOLE_H
#define FALLTERGEIST_LUA_CONSOLE_H

// C++ standard includes

// Falltergeist includes
#include "../Lua/Module.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

class Console : public Module
{
public:
    Console();
    virtual ~Console();

    virtual void attach(lua_State* L);

    static int debug(lua_State* L);
    static int info(lua_State* L);
    static int warning(lua_State* L);
    static int error(lua_State* L);
    static int critical(lua_State* L);


};

}
}
#endif // FALLTERGEIST_LUA_CONSOLE_H
