#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        class TransFlags
        {
            public:
                enum Trans {
                    DEFAULT = 0,
                    NONE,
                    WALL,
                    GLASS,
                    STEAM,
                    ENERGY,
                    RED
                };
        };
    }
}
