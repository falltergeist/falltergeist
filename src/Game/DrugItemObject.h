#pragma once

// Project includes
#include "../Game/ItemObject.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Item that can be consumed as drug (drugs, alcohol, food, etc.).
         * Applies temporary effect to a target critter.
         */
        class DrugItemObject : public ItemObject
        {
            public:
                DrugItemObject();
                ~DrugItemObject() = default;
        };
    }
}
