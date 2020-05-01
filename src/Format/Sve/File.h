#pragma once

#include <cstdint>
#include <map>
#include <string>
#include "../Dat/Item.h"

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
