#pragma once

#include "../Game/SceneryObject.h"
#include "../Game/LadderSceneryObject.h"

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
