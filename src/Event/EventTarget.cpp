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
#include "../Event/EventTarget.h"

// C++ standard includes
#include <type_traits>

// Falltergeist includes
#include "../Event/Dispatcher.h"
#include "../Event/Event.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Event/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        EventTarget::EventTarget(Dispatcher* eventDispatcher) : _eventDispatcher(eventDispatcher)
        {
        }

        EventTarget::~EventTarget()
        {
            // notify Event Dispatcher that this target was deleted, it should not process any further events for this object
            _eventDispatcher->blockEventHandlers(this);
        }

        template<typename T>
        void EventTarget::emitEvent(std::unique_ptr<T> event, const Base::Delegate<T*>& handler)
        {
            static_assert(std::is_base_of<Event, T>::value, "T should be derived from Event::Event.");
            if (handler)
            {
                event->setTarget(this);
                _eventDispatcher->scheduleEvent<T>(this, std::move(event), handler); // handler copy is necessary here
            }
        }

        // this was necessary to decouple EventDispatcher from the rest of the classes
        template void EventTarget::emitEvent<Event>(std::unique_ptr<Event>, const Base::Delegate<Event*>&);
        template void EventTarget::emitEvent<Mouse>(std::unique_ptr<Mouse>, const Base::Delegate<Mouse*>&);
        template void EventTarget::emitEvent<Keyboard>(std::unique_ptr<Keyboard>, const Base::Delegate<Keyboard*>&);
        template void EventTarget::emitEvent<State>(std::unique_ptr<State>, const Base::Delegate<State*>&);
    }
}
