#pragma once

// Project includes
#include "../../Format/Dat/Item.h"

// Third-party includes

// stdlib
#include <string>

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
