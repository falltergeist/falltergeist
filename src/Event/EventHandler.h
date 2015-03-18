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

#ifndef FALLTERGEIST_EVENTHANDLER_H
#define FALLTERGEIST_EVENTHANDLER_H

// C++ standard includes
#include <functional>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Event;
class EventSender;

class EventHandler
{

public:
    EventHandler(std::function<void(Event*)> handler);
    ~EventHandler();

    bool deleted() const;
    void setDeleted(bool value);

    EventSender* sender() const;
    void setSender(EventSender* sender);

    void operator()(Event*);

protected:

    bool _deleted = false;
    EventSender* _sender = nullptr;

    std::function<void(Event*)> _handler;

};

}
#endif // FALLTERGEIST_EVENTHANDLER_H
