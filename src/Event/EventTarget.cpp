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
#include "../Event/EventTarget.h"

// C++ standard includes

// Falltergeist includes
#include "../Event/Event.h"
#include "../Event/Dispatcher.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

EventTarget::EventTarget(Dispatcher* dispatcher) : _eventDispatcher(dispatcher)
{
}

EventTarget::~EventTarget()
{
    _eventDispatcher->removeEventHandler(this);
}

void EventTarget::addEventHandler(const std::string& eventName, EventTarget::Handler handler)
{
    _eventHandlers[eventName].push_back(handler);
}

void EventTarget::emitEvent(std::unique_ptr<Event> event)
{
    if (_eventHandlers.find(event->name()) == _eventHandlers.end()) return;

    _eventDispatcher->postEventHandler(shared_from_this(), std::move(event));
}

void EventTarget::processEvent(std::unique_ptr<Event> event)
{
    const auto it = _eventHandlers.find(event->name());
    if (it == _eventHandlers.end()) return;

    event->setEventTarget(this);
    for (auto eventHandler : it->second)
    {
        if (event->handled()) return;
        eventHandler(event.get());
    }
}

void EventTarget::removeEventHandlers(const std::string& eventName)
{
    const auto it = _eventHandlers.find(eventName);
    if (it == _eventHandlers.end()) return;

    it->second.clear();
    _eventHandlers.erase(it);
}

}
}
