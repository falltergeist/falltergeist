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

/**
 * Wrapper for LuaRef pointing to Lua table which acts as an instance of Lua "class" which "inherits" from C++ class.
 */
class Inheritable
{
public:
    Inheritable(luabridge::LuaRef table);

    /**
     * returns the underlying table
     */
    luabridge::LuaRef table() const;

    /**
     * sets table
     */
    void setTable(luabridge::LuaRef value);

    /**
     * Calls "method" with given name and zero or more arguments
     * Table itself will always be passed as a first ("self") argument, so you can take advantage of colon syntax in Lua.
     *
     * @return function result or nil if function with given name not exists
     */
    template<typename ...T>
    luabridge::LuaRef call(const std::string& method, T... args) const
    {
        luabridge::LuaRef ref(_table.state()); // init with nil reference
        if (_tryGetFunction(method, ref))
        {
            try
            {
                return ref(_table, args...);
            }
            catch (luabridge::LuaException ex)
            {
                _logError(ex.what());
            }
        }
        return ref;
    }

private:
    luabridge::LuaRef _table;

    bool _tryGetFunction(const std::string&, luabridge::LuaRef&) const;

    void _logError(const std::string& message) const;
};

}
}

#endif //FALLTERGEIST_INHERITABLE_H
