#pragma once

namespace Falltergeist
{
    namespace State
    {
        class Location;
    }
    namespace Helpers
    {
        class StateLocationHelper
        {
            public:
                StateLocationHelper() = default;
                std::unique_ptr<State::Location> getInitialLocationState() const;
        };
    }
}
