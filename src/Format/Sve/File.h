#pragma once

// Project includes
#include "../Dat/Item.h"

// Third-party includes

// stdlib
#include <cstdint>
#include <map>
#include <string>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Sve
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);
                    std::pair<int,std::string> getSubLine(int frame);

                protected:
                    std::map<int,std::string> _subs;
                    void _addString(std::string line);
            };
        }
    }
}
