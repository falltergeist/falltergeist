#pragma once

#include <memory>
#include <string>

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
                GameLocationHelper() = default;
                std::shared_ptr<Game::Location> getByName(const std::string& name) const;
                std::shared_ptr<Game::Location> getInitialLocation() const;
        };
    }
}
