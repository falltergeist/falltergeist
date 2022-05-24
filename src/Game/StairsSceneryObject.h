#pragma once

// Project includes
#include "../Game/SceneryObject.h"
#include "../Game/LadderSceneryObject.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        class StairsSceneryObject : public LadderSceneryObject
        {
            public:
                StairsSceneryObject();
                ~StairsSceneryObject() = default;
        };
    }
}
