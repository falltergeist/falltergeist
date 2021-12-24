#pragma once

#include <string>

#include "../Event/IEvent.h"

namespace Falltergeist
{
    namespace Event
    {
        class EventTarget;

        /**
         * @brief Base event class
         *
         * This class is base for all other event classes
         */
        class Event : public IEvent
        {
            public:
                Event(const std::string& name);

                virtual ~Event() override = default;

                const std::string& name() const override;

                EventTarget* target() const;
                void setTarget(EventTarget* value);

                bool handled() const;
                /**
                 * @brief Sets that event is handled or not.
                 * If called from within handle(Event*) function, affects event capturing process by preventing OS Event to "fall down" to other elements.
                 * If called from within the event handler function, prevents other handlers of the same event to be called.
                 * @param value the handled flag.
                 */
                void setHandled(bool value = true);

            protected:
                /// Is event handled or not
                bool _handled = false;
                /// Event name
                std::string _name;
                /// Event target
                EventTarget* _target = nullptr;
        };
    }
}
