#pragma once

#include <memory>

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            class Object;
            class Script;
        }
    }
    namespace Game
    {
        class Object;
    }
    namespace Helpers
    {
        class GameObjectHelper
        {
            public:
                GameObjectHelper() = default;
                std::shared_ptr<Game::Object> createFromMapObject(const std::unique_ptr<Falltergeist::Format::Map::Object> &mapObject) const;
                std::shared_ptr<Game::Object> createFromMapSpatialScript(const Format::Map::Script& mapScript) const;
        };
    }
}
