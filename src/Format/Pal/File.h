#pragma once

#include <vector>
#include "../Dat/Item.h"
#include "../Pal/Color.h"

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
