#pragma once

#include "../Event/Event.h"

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
