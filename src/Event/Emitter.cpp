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
#include "../Event/Emitter.h"

// C++ standard includes

// Falltergeist includes
#include "../Event/Event.h"
#include "../Event/Dispatcher.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

Emitter::Emitter(Dispatcher* dispatcher) : _eventDispatcher(dispatcher)
{
}

Emitter::~Emitter()
{
    _eventDispatcher->removeEventHandler(this);
}

void Emitter::addEventHandler(const std::string& eventName, Emitter::Handler handler)
{
    _eventHandlers[eventName].push_back(handler);
}

void Emitter::emitEvent(std::unique_ptr<Event> event)
{
    if (_eventHandlers.find(event->name()) == _eventHandlers.end()) return;

    _eventDispatcher->postEventHandler(this, std::move(event));
}

void Emitter::processEvent(std::unique_ptr<Event> event)
{
    const auto it = _eventHandlers.find(event->name());
    if (it == _eventHandlers.end()) return;
    event->setEmitter(this);
    for (auto eventHandler : it->second)
    {
        if (event->handled()) return;
        eventHandler(event.get());
    }
}

void Emitter::removeEventHandlers(const std::string& eventName)
{
    const auto it = _eventHandlers.find(eventName);
    if (it == _eventHandlers.end()) return;

    it->second.clear();
    _eventHandlers.erase(it);
}

}
}
