#pragma once

#include <memory>
#include <string>
#include "../ILogger.h"

namespace Falltergeist
{
    namespace Game
    {
        class Location;
    }
    namespace Helpers
    {
        class GameLocationHelper
        {
            public:
                GameLocationHelper(std::shared_ptr<ILogger> logger);
                std::shared_ptr<Game::Location> getByName(const std::string& name) const;
                std::shared_ptr<Game::Location> getInitialLocation() const;

            private:
                std::shared_ptr<ILogger> logger;
        };
    }
}
