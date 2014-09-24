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
 *
 */

#ifndef FALLTERGEIST_EVENTEMITTER_H
#define FALLTERGEIST_EVENTEMITTER_H

// C++ standard includes
#include <map>
#include <vector>
#include <string>
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Event;
class EventReciever;
class EventHandler;

typedef void (EventReciever::*EventRecieverMethod)(std::shared_ptr<Event>);

class EventEmitter
{
protected:
    std::map<std::string, std::vector<EventHandler*>> _eventHandlers;
public:
    EventEmitter();
    virtual ~EventEmitter();

    void addEventHandler(std::string eventName, EventReciever* reciever, EventRecieverMethod handler);
    void emitEvent(std::shared_ptr<Event> event);
    void removeEventHandlers(std::string eventName);
};

}
#endif // FALLTERGEIST_EVENTEMITTER_H
