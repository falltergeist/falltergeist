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

#ifndef FALLTERGEIST_EVENT_EMITTER_H
#define FALLTERGEIST_EVENT_EMITTER_H

// C++ standard includes
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Event
{
class Event;

class Dispatcher;

// TODO: make proper class with implicit conversion constructors
using EventHandler = std::function<void(Event*)>;

class EventTarget
{
public:

    EventTarget(Dispatcher* eventDispatcher);
    virtual ~EventTarget();

    /**
     * Adds event handler to given event name.
     */
    void addEventHandler(const std::string& eventName, EventHandler handler);
    /**
     * Immediately start processing of event by calling each associated handler.
     */
    //void processEvent(Event* event);
    /**
     * Emit given event to Event Dispatcher for delayed processing.
     */
    void emitEvent(std::unique_ptr<Event> event);
    /**
     * Remove all event handlers attached to given event name.
     */
    void removeEventHandlers(const std::string& eventName);

protected:
    std::map<std::string, std::list<EventHandler>> _eventHandlers;
    Dispatcher* _eventDispatcher;
};

}
}
#endif // FALLTERGEIST_EVENT_EMITTER_H
