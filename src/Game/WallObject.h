#pragma once

#include "../Game/Object.h"

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Walls
         */
        class WallObject : public Object
        {
            public:
                WallObject();
                ~WallObject() = default;
        };
    }
}
