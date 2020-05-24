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
                std::unique_ptr<Game::Location> getByName(const std::string& name) const;
                std::unique_ptr<Game::Location> getInitialLocation() const;
        };
    }
}
