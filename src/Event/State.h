#pragma once

// Project includes
#include "../Event/Event.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Event
    {
        class State : public Event
        {
            public:
                State(const std::string& name);
                ~State() override;
        };
    }
}
