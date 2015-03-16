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
    if(!_instance)
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

    for(auto map : _handlers.at(event->name()))
    {
        if (map.first == nullptr || map.first == event->sender())
        {
            for (auto& handler : map.second)
            {
                if (event->handled())
                {
                    break;
                }
                handler(event);
            }
        }
    }
    think();
}

void EventManager::addHandler(std::string eventName, std::function<void(Event*)> handler, EventSender* sender)
{
    // if such eventName is not registered yet
    if (_handlers.find(eventName) == _handlers.end())
    {
        std::map<EventSender*, std::vector<std::function<void(Event*)>>> map;
        _handlers.insert(std::make_pair(eventName, map));
    }

    // if such sender is not registered yet
    if (_handlers.at(eventName).find(sender) == _handlers.at(eventName).end())
    {
        std::vector<std::function<void(Event*)>> vector;
        _handlers.at(eventName).insert(std::make_pair(sender, vector));
    }

    _handlers.at(eventName).at(sender).push_back(handler);
}

void EventManager::removeHandlers(EventSender* sender)
{
    for(auto& map : _handlers)
    {
        removeHandlers(map.first, sender);
    }
}

void EventManager::removeHandlers(std::string eventName, EventSender* sender)
{
    // if such eventName is not registered
    if (_handlers.find(eventName) == _handlers.end())
    {
        return;
    }

    if (_handlersToDelete.find(eventName) == _handlersToDelete.end())
    {
        std::vector<EventSender*> vector;
        _handlersToDelete.insert(std::make_pair(eventName, vector));
    }

    _handlersToDelete.at(eventName).push_back(sender);
}

void EventManager::think()
{
    for (auto map : _handlersToDelete)
    {
        for (auto sender : map.second)
        {
            // remove all handlers
            if (sender == nullptr)
            {
                _handlers.erase(map.first);
            }
            else
            {
                // if such sender is not registered
                if (_handlers.at(map.first).find(sender) == _handlers.at(map.first).end())
                {
                    continue;
                }

                _handlers.at(map.first).erase(sender);
            }
        }
    }
}


}
