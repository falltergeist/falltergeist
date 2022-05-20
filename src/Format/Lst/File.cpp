#include <algorithm>
#include <functional>
#include <cctype>
#include "../Dat/Stream.h"
#include "../Lst/File.h"
#include "../../functions.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Lst
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);

                std::string line;
                unsigned char ch = 0;
                for (unsigned int i = 0; i != stream.size(); ++i)
                {
                    stream >> ch;
                    if (ch == 0x0D) // \r
                    {
                        // do nothing
                    }
                    else if (ch == 0x0A) // \n
                    {
                        _addString(line);
                        line.clear();
                    }
                    else
                    {
                        line += ch;
                    }
                }
                if (line.size() != 0)
                {
                    _addString(line);
                }
            }

            void File::_addString(std::string line)
            {
                // strip comments
                if (auto pos = line.find(";")) {
                    line = line.substr(0, pos);
                }

                // rtrim
                frtrim(line);

                // replace slashes
                std::replace(line.begin(),line.end(),'\\','/');

                // to lower
                std::transform(line.begin(),line.end(),line.begin(), ::tolower);

                _strings.push_back(line);
            }

            std::vector<std::string>* File::strings()
            {
                return &_strings;
            }
        }
    }
}
