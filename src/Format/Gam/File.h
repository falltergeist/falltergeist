#pragma once

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

        namespace Gam
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);
                    std::map<std::string, int>* GVARS();
                    std::map<std::string, int>* MVARS();
                    int GVAR(std::string name);
                    int GVAR(unsigned int number);
                    int MVAR(std::string name);
                    int MVAR(unsigned int number);

                protected:
                    std::map<std::string, int> _GVARS;
                    std::map<std::string, int> _MVARS;
                    bool _GVARmode = false;
                    bool _MVARmode = false;
                    void _parseLine(std::string line);
            };
        }
    }
}
