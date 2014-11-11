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
#include "../Event/EventEmitter.h"
#include "../Event/EventHandler.h"
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

EventEmitter::EventEmitter()
{
}

EventEmitter::~EventEmitter()
{
}

void EventEmitter::addEventHandler(std::string eventName, EventReciever* reciever, EventRecieverMethod handler)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end())
    {
        std::vector<EventHandler*> vector;
        _eventHandlers.insert(std::make_pair(eventName, vector));
    }

    _eventHandlers.at(eventName).push_back(new EventHandler(reciever, handler));
}

void EventEmitter::emitEvent(Event* event)
{
    if (_eventHandlers.find(event->name()) == _eventHandlers.end()) return;
    event->setEmitter(this);
    for (auto eventHandler : _eventHandlers.at(event->name()))
    {
        if (event->handled()) return;
        event->setReciever(eventHandler->reciever());
        eventHandler->operator()(event);
    }
}

void EventEmitter::removeEventHandlers(std::string eventName)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end()) return;

    while (!_eventHandlers.at(eventName).empty())
    {
        delete _eventHandlers.at(eventName).back();
        _eventHandlers.at(eventName).pop_back();
    }
    _eventHandlers.erase(eventName);
}

}
