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
#include "../Event/Emitter.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

void Dispatcher::postEventHandler(Emitter* emitter, std::unique_ptr<Event> event)
{
    _scheduledEvents.emplace_back(emitter, std::move(event));
}

void Dispatcher::processScheduledEvents()
{
    using std::swap;

    if (_scheduledEvents.empty())
        return;

    decltype(_scheduledEvents) copyOfEvents;
    swap(copyOfEvents, _scheduledEvents);
    for (auto& task : copyOfEvents)
    {
        task.first->processEvent(std::move(task.second));
    }
}

void Dispatcher::removeEventHandler(Emitter* emitter)
{
    using ElemType = decltype(_scheduledEvents)::value_type;

    _scheduledEvents.remove_if([emitter](const ElemType& elem)
    {
        return emitter == elem.first;
    });
}

}
}
