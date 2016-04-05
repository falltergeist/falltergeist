/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <functional>
#include <type_traits>
#include <utility>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Event/EventTarget.h"
#include "../Event/Event.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Event/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        using namespace Base;

        Dispatcher::AbstractTask::AbstractTask(EventTarget* target) : target(target) {}

        template <typename T>
        Dispatcher::Task<T>::Task(EventTarget* target, std::unique_ptr<T> event, Base::Delegate<T*> handler)
            : AbstractTask(target), event(std::move(event)), handler(handler)
        {
            static_assert(std::is_base_of<Event, T>::value, "T should be derived from Event::Event.");
        }

        template <typename T>
        void Dispatcher::Task<T>::perform()
        {
            event->setHandled(false);
            for (auto& func : handler.functors())
            {
                func(event.get());
                // handler may set handled flag to true - to stop other handlers from executing
                // also, target may be deleted by any handler, so we should check that on every iteration
                if (event->handled() || target == nullptr) break;
            }
        }

        template<typename T>
        void Dispatcher::scheduleEvent(EventTarget* target, std::unique_ptr<T> eventArg, Base::Delegate<T*> handlerArg)
        {
            _scheduledTasks.emplace_back(make_unique<Task<T>>(target, std::move(eventArg), std::move(handlerArg)));
        }

        void Dispatcher::processScheduledEvents()
        {
            while (!_scheduledTasks.empty())
            {
                swap(_tasksInProcess, _scheduledTasks);
                for (auto& task : _tasksInProcess)
                {
                    // after previous tasks this target might already be "dead"
                    if (task->target == nullptr) continue;
                    task->perform();
                }
                _tasksInProcess.clear();
            }
        }

        void Dispatcher::blockEventHandlers(EventTarget* eventTarget)
        {
            _scheduledTasks.remove_if([eventTarget](std::unique_ptr<Dispatcher::AbstractTask>& task)
            {
                return (task->target == eventTarget);
            });
            for (auto& task : _tasksInProcess)
            {
                if (task->target == eventTarget)
                {
                    task->target = nullptr;
                }
            }
        }

        // instantiations for all event types..
        template void Dispatcher::scheduleEvent<Event>(EventTarget*, std::unique_ptr<Event>, Base::Delegate<Event*>);
        template void Dispatcher::scheduleEvent<Mouse>(EventTarget*, std::unique_ptr<Mouse>, Base::Delegate<Mouse*>);
        template void Dispatcher::scheduleEvent<Keyboard>(EventTarget*, std::unique_ptr<Keyboard>, Base::Delegate<Keyboard*>);
        template void Dispatcher::scheduleEvent<State>(EventTarget*, std::unique_ptr<State>, Base::Delegate<State*>);
    }
}
