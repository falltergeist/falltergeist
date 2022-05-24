#pragma once

// Project includes
#include "../Game/Object.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        class SpatialObject : public Object
        {
            public:
                explicit SpatialObject(unsigned int radius);
                ~SpatialObject() = default;

                void spatial_p_proc(Object* source);
                unsigned int radius();

            private:
                unsigned int _radius;
        };
    }
}
