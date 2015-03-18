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

// Falltergeist includes
#include "../Event/EventManager.h"
#include "../Event/EventSender.h"

// Third party includes

namespace Falltergeist
{

EventSender::EventSender()
{
}

EventSender::~EventSender()
{
    EventManager::getInstance()->removeHandlers(this);
}

void EventSender::addEventHandler(std::string eventName, std::function<void(Event*)> handler)
{
    EventManager::getInstance()->addHandler(eventName, handler, this);
}

void EventSender::removeEventHandlers(std::string eventName)
{
    EventManager::getInstance()->removeHandlers(eventName, this);
}

void EventSender::removeEventHandlers()
{
    EventManager::getInstance()->removeHandlers(this);
}

}
