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

#ifndef FALLTERGEIST_EVENT_DISPATCHER_H
#define FALLTERGEIST_EVENT_DISPATCHER_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Event
{
class Event;
class Emitter;

class Dispatcher
{
public:
    static Dispatcher* getInstance();

    virtual void postEventHandler(Emitter* emitter, Event* event) = 0;
    virtual void removeEventHandler(Emitter* emitter) = 0;
};

}
}
#endif // FALLTERGEIST_EVENT_DISPATCHER_H
