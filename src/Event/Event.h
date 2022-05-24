#pragma once

// Project includes
#include "../Event/IEvent.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist {
    namespace Event {
        class EventTarget;

        /**
         * @brief Base event class
         *
         * This class is base for all other event classes
         */
        class Event : public IEvent {
        public:
            Event(const std::string& name);

            virtual ~Event() override = default;

            const std::string& name() const override;

            bool isHandled() const override;

            /**
             * @brief Sets that event is handled.
             * If called from within handle(Event*) function, affects event capturing process by preventing OS Event to "fall down" to other elements.
             * If called from within the event handler function, prevents other handlers of the same event to be called.
             */
            void stopPropagation() override;

        protected:
            bool _handled = false;

            std::string _name;
        };
    }
}
