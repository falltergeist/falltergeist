#pragma once

#include <string>

namespace Falltergeist {
    namespace Event {
        class IEvent {
        public:
            virtual ~IEvent() = default;

            virtual const std::string& name() const = 0;
        };
    }
}
