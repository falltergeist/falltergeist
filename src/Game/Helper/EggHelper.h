#pragma once

// Project includes

// Third-party includes

// stdlib
#include <memory>

namespace Falltergeist
{
    namespace Game
    {
        class DudeObject;
        class Object;

        namespace Helper
        {
            class EggHelper
            {
                public:
                    EggHelper() = default;
                    ~EggHelper() = default;
                    bool isTransparentForEgg(const Object* object, const std::shared_ptr<DudeObject>& dude);
            };
        }
    }
}
