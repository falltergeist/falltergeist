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

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../Event/EventHandler.h"
#include "../Event/EventManager.h"
#include "../Event/EventSender.h"

// Third party includes

namespace Falltergeist
{

EventManager* EventManager::_instance = nullptr;

EventManager::EventManager()
{
}

EventManager* EventManager::getInstance()
{
    if (!_instance)
    {
        _instance = new EventManager();
    }
    return _instance;
}

void EventManager::handle(Event* event)
{
    // if such eventName is not registered
    if (_handlers.find(event->name()) == _handlers.end())
    {
        return;
    }

    // Iterating thru handlers with given eventName
    for (auto handler : _handlers.at(event->name()))
    {
        if (event->handled()) return;
        if (handler->deleted()) continue;

        if (handler->sender() == nullptr || handler->sender() == event->sender())
        {
            (*handler)(event);
        }
    }
}

void EventManager::addHandler(std::string eventName, std::function<void(Event*)> function, EventSender* sender)
{
    // if such eventName is not registered yet
    if (_handlers.find(eventName) == _handlers.end())
    {
        _handlers.insert(std::make_pair(eventName, std::vector<EventHandler*>()));
    }

    auto handler = new EventHandler(function);
    handler->setSender(sender);

    _handlers.at(eventName).push_back(handler);
}

void EventManager::removeHandlers(EventSender* sender)
{
    for (auto& map : _handlers)
    {
        for (auto handler : map.second)
        {
            if (handler->sender() == sender)
            {
                handler->setDeleted(true);
            }
        }
    }
}

void EventManager::removeHandlers(std::string eventName, EventSender* sender)
{
    // if such eventName is not registered
    if (_handlers.find(eventName) == _handlers.end())
    {
        return;
    }

    for (auto handler : _handlers.at(eventName))
    {
        if (sender == nullptr || handler->sender() == sender)
        {
            handler->setDeleted(true);
        }
    }
}

void EventManager::think()
{
    for (auto& map : _handlers)
    {
        for (auto it = map.second.begin(); it != map.second.end();)
        {
            if ((*it)->deleted())
            {
                delete *it;
                it = map.second.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

}
