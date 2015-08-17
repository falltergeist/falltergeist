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

#ifndef FALLTERGEIST_EVENT_EVENT_H
#define FALLTERGEIST_EVENT_EVENT_H

// C++ standard includes
#include <memory>
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Lua
{
    class Script;
}
namespace Event
{
class Emitter;

class Event
{
public:
    Event(const std::string& name);
    virtual ~Event();

    std::string name() const;
    void setName(const std::string& name);

    Emitter* emitter() const;
    void setEmitter(Emitter* value);

    bool handled() const;
    void setHandled(bool value);

    static void export_to_lua_script(Lua::Script* script);

protected:
    std::string _name;
    Emitter* _emitter = 0;
    bool _handled = false;
};

}
}
#endif // FALLTERGEIST_EVENT_EVENT_H
