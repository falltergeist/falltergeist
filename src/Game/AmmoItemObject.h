#pragma once

#include "../Game/ItemObject.h"

namespace Falltergeist
{
    namespace Game
    {
        class AmmoItemObject : public ItemObject
        {
            public:
                AmmoItemObject();
                ~AmmoItemObject() override = default;
        };
    }
}
