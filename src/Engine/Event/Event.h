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

#ifndef FALLTERGEIST_EVENT_H
#define FALLTERGEIST_EVENT_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Event/EventEmitter.h"
#include "../Event/EventHandler.h"
#include "../Event/EventReciever.h"

// Third party includes

namespace Falltergeist
{

class InteractiveSurface;

class Event
{
protected:
    std::string _name;
    EventEmitter* _emitter = 0;
public:
    Event(std::string name);
    virtual ~Event();
    std::string name();
    void setName(std::string name);

    EventEmitter* emitter();
    void setEmitter(EventEmitter* value);
};

}
#endif // FALLTERGEIST_EVENT_H
