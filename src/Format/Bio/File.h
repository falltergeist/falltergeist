#pragma once

#include <string>
#include "../../Format/Dat/Item.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Bio
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    std::string text();

                protected:
                    std::string _text;
            };
        }
    }
}
