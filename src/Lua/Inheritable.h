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

#ifndef FALLTERGEIST_INHERITABLE_H
#define FALLTERGEIST_INHERITABLE_H

// C++ standard includes

// Libfalltergeist includes

// Third party includes
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
}
#include "LuaBridge.h"

namespace Falltergeist
{
namespace Lua
{


class Inheritable
{
public:
    Inheritable(lua_State* L);

    void setSubclassTable(luabridge::LuaRef value);

    // calls given method with only self argument
    luabridge::LuaRef callTableMethod(const std::string&) const;

    // calls given method with self and one argument
    template <class T1>
    luabridge::LuaRef callTableMethod(const std::string& method, T1 a1) const
    {
        return _callTableMethodInternal(method, [this, a1](luabridge::LuaRef func){ return func(_subclassTable, a1); });
    }

    // calls given method with self and two arguments
    template <class T1, class T2>
    luabridge::LuaRef callTableMethod(const std::string& method, T1 a1, T2 a2) const
    {
        return _callTableMethodInternal(method, [this, a1, a2](luabridge::LuaRef func){ return func(_subclassTable, a1, a2); });
    }

    // calls given method with self and three arguments
    template <class T1, class T2, class T3>
    luabridge::LuaRef callTableMethod(const std::string& method, T1 a1, T2 a2, T3 a3) const
    {
        return _callTableMethodInternal(method, [this, a1, a2, a3](luabridge::LuaRef func){ return func(_subclassTable, a1, a2, a3); });
    }

    // calls given method with self and four arguments
    template <class T1, class T2, class T3, class T4>
    luabridge::LuaRef callTableMethod(const std::string& method, T1 a1, T2 a2, T3 a3, T4 a4) const
    {
        return _callTableMethodInternal(method, [this, a1, a2, a3, a4](luabridge::LuaRef func){ return func(_subclassTable, a1, a2, a3, a4); });
    }

private:
    luabridge::LuaRef _subclassTable;

    luabridge::LuaRef _callTableMethodInternal(const std::string&, std::function<luabridge::LuaRef(luabridge::LuaRef)>) const;
};

}
}

#endif //FALLTERGEIST_INHERITABLE_H
