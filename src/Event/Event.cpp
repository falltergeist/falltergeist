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

// Related headers
#include "../Event/Event.h"

// C++ standard includes

// Falltergeist includes
#include "../Lua/Script.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

Event::Event(const std::string& name)
{
    _name = name;
}

Event::~Event()
{
}

void Event::export_to_lua_script(Lua::Script* script)
{
    luabridge::getGlobalNamespace(script->luaState())
        .beginNamespace("game")
            .beginClass<Event>("Event")
                .addProperty("name", &Event::name, &Event::setName)
            .endClass()
        .endNamespace();
}

std::string Event::name() const
{
    return _name;
}

void Event::setName(const std::string& name)
{
    _name = name;
}

Emitter* Event::emitter() const
{
    return _emitter;
}

void Event::setEmitter(Emitter* value)
{
    _emitter = value;
}

bool Event::handled() const
{
    return _handled;
}

void Event::setHandled(bool value)
{
    _handled = value;
}

}
}
