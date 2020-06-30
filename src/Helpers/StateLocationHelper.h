#pragma once

#include <memory>
#include "../ILogger.h"

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
                StateLocationHelper(std::shared_ptr<ILogger> logger);
                State::Location* getInitialLocationState() const;
            private:
                std::shared_ptr<ILogger> logger;
        };
    }
}
