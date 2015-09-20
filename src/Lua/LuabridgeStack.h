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

#ifndef FALLTERGEIST_LUA_LUABRIDGESTACK_H
#define FALLTERGEIST_LUA_LUABRIDGESTACK_H

// C++ standard includes


// Libfalltergeist includes
#include "../Event/Event.h"
#include "../Exception.h"
#include "../Lua/Binder.h"

// Third party includes
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "LuaBridge.h"


/**
 * Specializations for luabridge::Stack<T>.
 */
namespace luabridge
{

/**
 * Stack specialization for Event Handler functions
 */
template<>
struct Stack<std::function<void(Falltergeist::Event::Event*)>>
{
public:
    static inline std::function<void(Falltergeist::Event::Event*)> get(lua_State* L, int index)
    {
        LuaRef ref = LuaRef::fromStack(L, index);
        if (ref.isFunction())
        {
            return [ref](Falltergeist::Event::Event* event)
            {
                // TODO: should pass self as first argument?
                ref(event);
            };
        }
        throw Falltergeist::Exception("Event handler is not a function!");
    }
};

}

#endif //FALLTERGEIST_LUA_LUABRIDGESTACK_H
