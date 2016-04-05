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

#ifndef FALLTERGEIST_EVENT_DISPATCHER_H
#define FALLTERGEIST_EVENT_DISPATCHER_H

// C++ standard includes
#include <list>
#include <memory>

// Falltergeist includes
#include "../Event/Event.h"
#include "../Event/EventTarget.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class Dispatcher
        {
            public:
                Dispatcher() {}

                template<typename T>
                void scheduleEvent(EventTarget* target, std::unique_ptr<T> eventArg, Base::Delegate<T*> handlerArg);

                void processScheduledEvents();
                void blockEventHandlers(EventTarget* eventTarget);

            private:
                struct AbstractTask
                {
                    AbstractTask(EventTarget* target);
                    EventTarget* target;
                    virtual void perform() = 0;
                };

                template <typename T>
                struct Task : AbstractTask
                {
                    Task(EventTarget* target, std::unique_ptr<T> event, Base::Delegate<T*> handler);
                    void perform() override;

                    std::unique_ptr<T> event;
                    Base::Delegate<T*> handler;
                };


                Dispatcher(const Dispatcher&) = delete;
                void operator=(const Dispatcher&) = delete;

                std::list<std::unique_ptr<AbstractTask>> _scheduledTasks, _tasksInProcess;
        };
    }
}
#endif // FALLTERGEIST_EVENT_DISPATCHER_H
