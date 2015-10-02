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
#include "EventTarget.h"

// C++ standard includes

// Falltergeist includes
#include "../Event/Dispatcher.h"
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

EventTarget::EventTarget(Dispatcher* eventDispatcher) : _eventDispatcher(eventDispatcher)
{
}

EventTarget::~EventTarget()
{
    // notify Event Dispatcher that this target was deleted, it should not process any further events for this object
    _eventDispatcher->blockEventHandlers(this);
}

void EventTarget::addEventHandler(const std::string& eventName, EventHandler handler)
{
    _eventHandlers[eventName].push_back(handler);
}

/*void EventTarget::processEvent(Event* event)
{
    const auto it = _eventHandlers.find(event->name());
    event->setHandled(false);
    if (it != _eventHandlers.end())
    {
        event->setTarget(this);
        for (auto& eventHandler : it->second)
        {
            if (event->handled()) return;
            eventHandler(event);
        }
    }
}*/

void EventTarget::emitEvent(std::unique_ptr<Event> event)
{
    const auto it = _eventHandlers.find(event->name());
    if (it != _eventHandlers.end())
    {
        event->setTarget(this);
        _eventDispatcher->scheduleEvent(std::move(event), &it->second);
    }
}

void EventTarget::removeEventHandlers(const std::string& eventName)
{
    const auto it = _eventHandlers.find(eventName);
    if (it != _eventHandlers.end())
    {
        _eventHandlers.erase(it);
    }
}

}
}
