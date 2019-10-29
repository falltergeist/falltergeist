#pragma once

#include "../Game/CritterObject.h"

namespace Falltergeist
{
    namespace Helpers
    {
        class CritterHelper
        {
            public:
                CritterHelper() = default;
                uint32_t armorFID(Game::CritterObject* critter) const;
                uint32_t weaponId(Game::CritterObject* critter) const;
        };
    }
}
