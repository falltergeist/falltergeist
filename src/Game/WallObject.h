#pragma once

// Project includes
#include "../Game/Object.h"

// Third-party includes

// stdlib

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
