#pragma once

#include "../Game/SceneryObject.h"

namespace Falltergeist
{
    namespace Game
    {
        class LadderSceneryObject : public SceneryObject
        {
            public:
                LadderSceneryObject();
                ~LadderSceneryObject() override = default;
        };
    }
}
