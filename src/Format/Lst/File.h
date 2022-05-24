#pragma once

// Project includes
#include "../Dat/Item.h"

// Third-party includes

// stdlib
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Lst
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    // TODO: return by reference
                    std::vector<std::string>* strings();

                protected:
                    std::vector<std::string> _strings;
                    void _addString(std::string line);
            };
        }
    }
}
