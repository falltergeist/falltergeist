#pragma once

#include <memory>
#include "../ILogger.h"

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
