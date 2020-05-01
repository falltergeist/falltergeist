#pragma once

#include <string>

namespace Falltergeist
{
    namespace Helpers
    {
        class CritterAnimationHelper
        {
            public:
                CritterAnimationHelper() = default;
                std::string getSuffix(unsigned int animationId, unsigned int weaponId) const;
                std::string getPrefix(unsigned int FID) const;
        };
    }
}
