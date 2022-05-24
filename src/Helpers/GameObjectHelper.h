#pragma once

// Project includes
#include "../ILogger.h"

// Third-party includes

// stdlib
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
                GameObjectHelper(std::shared_ptr<ILogger> logger);
                Game::Object* createFromMapObject(const std::unique_ptr<Format::Map::Object> &mapObject) const;
                Game::Object* createFromMapSpatialScript(const Format::Map::Script& mapScript) const;
            private:
                std::shared_ptr<ILogger> logger;
        };
    }
}
