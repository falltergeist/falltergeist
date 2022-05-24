#pragma once

// Project includes

// Third-party includes

// stdlib
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
