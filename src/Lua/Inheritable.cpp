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
#include <functional>

// Libfalltergeist includes
#include "../Exception.h"
#include "../Logger.h"
#include "../Lua/Inheritable.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

Inheritable::Inheritable(luabridge::LuaRef table) : _table(table)
{
    if (table.type() != LUA_TTABLE) {
        throw Exception("Inheritable(): Value is not a table: " + table.tostring());
    }
}

luabridge::LuaRef Inheritable::table() const
{
    return _table;
}

void Inheritable::setTable(luabridge::LuaRef value)
{
    if (value.isTable())
    {
        _table = value;
    }
    else
    {
        Logger::error("Lua") << "Inheritable::setInheritedTable(): Value is not a table: " << value << std::endl;
    }
}

luabridge::LuaRef Inheritable::call(const std::string& method) const
{
    return _callInternal(method, [this](luabridge::LuaRef func)
    {
        return func(_table);
    });
}


luabridge::LuaRef Inheritable::_callInternal(const std::string& method,
                                             std::function<luabridge::LuaRef(luabridge::LuaRef)> handler) const
{
    if (_table[method].isFunction())
    {
        return handler(_table[method]);
    }
    else
    {
        Logger::error("Lua") << "Inheritable::call(): value is not a function: " << luabridge::LuaRef(_table[method]);
    }
    return luabridge::LuaRef(_table.state());
}
}
}