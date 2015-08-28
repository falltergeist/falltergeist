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
#include "../Event/Dispatcher.h"

// C++ standard includes

// Falltergeist includes
#include "../Event/EventTarget.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

void Dispatcher::postEventHandler(EventTarget* EventTarget, std::unique_ptr<Event> event)
{
    _scheduledEvents.emplace_back(EventTarget, std::move(event));
}

void Dispatcher::processScheduledEvents()
{
    using std::swap;

    while (!_scheduledEvents.empty())
    {
        decltype(_scheduledEvents) copyOfEvents;
        swap(copyOfEvents, _scheduledEvents);
        auto it = copyOfEvents.begin();
        while (it != copyOfEvents.end())
        {
            it->first->processEvent(std::move(it->second));
            ++it;
            if (!_deletedTargets.empty())
            {
                for (; _deletedTargets.count(it->first) > 0 && it != copyOfEvents.end(); ++it)
                {}

                using ElemType = decltype(copyOfEvents)::value_type;
                copyOfEvents.remove_if([this](const ElemType& elem)
                {
                    return _deletedTargets.count(elem.first) > 0;
                });

                _deletedTargets.clear();
            }
        }
    }
}

void Dispatcher::removeEventHandler(EventTarget* eventTarget)
{
    using ElemType = decltype(_scheduledEvents)::value_type;

    _scheduledEvents.remove_if([eventTarget](const ElemType& elem)
    {
        return eventTarget == elem.first;
    });
    _deletedTargets.insert(eventTarget);
}

}
}
