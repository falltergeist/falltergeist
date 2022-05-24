#pragma once

// Project includes
#include "../ILogger.h"

// Third-party includes

// stdlib
#include <memory>

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
                State::Location* getCustomLocationState(const std::string& name, uint32_t elevation, uint32_t position) const;
            private:
                std::shared_ptr<ILogger> logger;
        };
    }
}
