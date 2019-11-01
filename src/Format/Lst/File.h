#pragma once

#include <string>
#include <vector>
#include "../Dat/Item.h"

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
