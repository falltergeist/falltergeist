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

void Dispatcher::scheduleEvent(EventTarget* target, std::unique_ptr<Event> event)
{
    _scheduledTasks.emplace_back(target, std::move(event));
}

void Dispatcher::processScheduledEvents()
{
    while (!_scheduledTasks.empty())
    {
        swap(_tasksInProcess, _scheduledTasks);
        for (Task& task : _tasksInProcess)
        {
            // after previous tasks this target might already be "dead"
            if (task.first == nullptr) continue;

            // any handler can alter current list of handlers by calling addEventHandler or removeEventHandlers on target,
            // so we have to use copy here
            auto handler = task.first->getEventHandler(task.second->name());

            task.second->setHandled(false);
            for (auto& func : handler.functors())
            {
                func(task.second.get());
                // handler may set handled flag to true - to stop other handlers from executing
                // also, target may be deleted by any handler, so we should check that on every iteration
                if (task.second->handled() || task.first == nullptr) break;
            }
        }
        _tasksInProcess.clear();
    }
}

void Dispatcher::blockEventHandlers(EventTarget* eventTarget)
{
    _scheduledTasks.remove_if([eventTarget](Dispatcher::Task& task)
    {
        return (task.first == eventTarget);
    });
    for (auto& task : _tasksInProcess)
    {
        if (task.first == eventTarget)
        {
            task.first = nullptr;
        }
    }
}

}
}
