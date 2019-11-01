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
                State::Location* getInitialLocationState() const;
        };
    }
}
