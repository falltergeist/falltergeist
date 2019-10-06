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
                Game::Object* createFromMapObject(const std::unique_ptr<Format::Map::Object> &mapObject) const;
                Game::Object* createFromMapSpatialScript(const Format::Map::Script& mapScript) const;
        };
    }
}
