#pragma once

#include "../Game/SceneryObject.h"

namespace Falltergeist
{
    namespace Game
    {
        class GenericSceneryObject : public SceneryObject
        {
            public:
                GenericSceneryObject();
                ~GenericSceneryObject() override = default;

            protected:
                bool _useEggTransparency() override;
        };
    }
}
