/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

Event::Event(std::string name)
{
    _name = name;
}

Event::~Event()
{
}

std::string Event::name()
{
    return _name;
}

void Event::setName(std::string name)
{
    _name = name;
}

EventEmitter* Event::emitter()
{
    return _emitter;
}

void Event::setEmitter(EventEmitter* value)
{
    _emitter = value;
}

EventReciever* Event::reciever()
{
    return _reciever;
}

void Event::setReciever(EventReciever* reciever)
{
    _reciever = reciever;
}

}
