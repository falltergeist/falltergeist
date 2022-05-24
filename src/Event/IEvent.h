#pragma once

// Project includes

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist {
    namespace Event {
        class IEvent {
        public:
            virtual ~IEvent() = default;

            virtual const std::string& name() const = 0;

            virtual bool isHandled() const = 0;

            virtual void stopPropagation() = 0;
        };
    }
}
