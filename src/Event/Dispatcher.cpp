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

Dispatcher::Task::Task(std::unique_ptr<Event> event, std::list<EventHandler>* handlers)
    : event(std::move(event)), handlers(handlers)
{
}

void Dispatcher::scheduleEvent(std::unique_ptr<Event> event, std::list<EventHandler>* handlers)
{
    _scheduledTasks.emplace_back(std::move(event), handlers);
}

void Dispatcher::processScheduledEvents()
{
    while (!_scheduledTasks.empty())
    {
        swap(_tasksInProcess, _scheduledTasks);
        for (Task& task : _tasksInProcess)
        {
            // after previous tasks this target might already be "dead"
            if (task.handlers != nullptr)
            {
                task.event->setHandled(false);
                for (auto& handler : *task.handlers)
                {
                    handler(task.event.get());
                    // handler may set handled flag to true - to stop other handlers from executing
                    // also, target may be deleted by any handler, so we should check that on every iteration
                    if (task.event->handled() || task.handlers == nullptr) break;
                }
            }
        }
        _tasksInProcess.clear();
    }
}

void Dispatcher::blockEventHandlers(EventTarget* eventTarget)
{
    _scheduledTasks.remove_if([eventTarget](Dispatcher::Task& task)
    {
        return (task.event->target() == eventTarget);
    });
    for (auto& task : _tasksInProcess)
    {
        if (task.event->target() == eventTarget)
        {
            task.event->setTarget(nullptr);
            task.handlers = nullptr;
        }
    }
}

}
}
