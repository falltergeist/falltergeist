#pragma once

// Project includes
#include "../Dat/Item.h"
#include "../Pal/Color.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Pal
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    const Color* color(unsigned index) const;

                protected:
                    std::vector<Color> _colors;
            };
        }
    }
}
