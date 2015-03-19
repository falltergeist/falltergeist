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

#ifndef FALLTERGEIST_EVENTMANAGER_H
#define FALLTERGEIST_EVENTMANAGER_H

// C++ standard includes
#include <functional>
#include <map>
#include <string>
#include <vector>

// Falltergeist includes
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

class EventHandler;
class EventSender;

class EventManager
{

public:
    static EventManager* getInstance();
    void handle(Event* event);
    void addHandler(std::string eventName, std::function<void(Event*)> function, EventSender* sender = nullptr);
    void removeHandlers(std::string eventName, EventSender* sender = nullptr);
    void removeHandlers(EventSender *sender = nullptr);
    void think();

protected:
    static EventManager* _instance;
    std::map<std::string, std::vector<EventHandler*>> _handlers;

    EventManager();
    EventManager(const EventManager&);
    EventManager& operator=(EventManager&);
    ~EventManager();

};

}
#endif // FALLTERGEIST_EVENTMANAGER_H
