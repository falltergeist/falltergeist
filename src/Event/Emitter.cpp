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

// Third party includes

namespace Falltergeist
{
namespace Event
{

Emitter::Emitter()
{
}

Emitter::~Emitter()
{
}

void Emitter::addEventHandler(const std::string& eventName, std::function<void(Event*)> handler)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end())
    {
        std::vector<std::function<void(Event*)>> vector;
        _eventHandlers.insert(std::make_pair(eventName, vector));
    }

    _eventHandlers.at(eventName).push_back(handler);
}

void Emitter::emitEvent(Event* event)
{
    if (_eventHandlers.find(event->name()) == _eventHandlers.end()) return;
    event->setEmitter(this);
    for (auto eventHandler : _eventHandlers.at(event->name()))
    {
        if (event->handled()) return;
        eventHandler(event);
    }
}

void Emitter::removeEventHandlers(const std::string& eventName)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end()) return;

    _eventHandlers.at(eventName).clear();
    _eventHandlers.erase(eventName);
}

}
}
