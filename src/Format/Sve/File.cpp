// Project includes
#include "../../Exception.h"
#include "../Dat/Stream.h"
#include "../Sve/File.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Sve
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
                auto pos = line.find(":");
                if (pos != std::string::npos)
                {
                    auto frame = line.substr(0, pos);
                    line = line.substr(pos+1);
                    _subs.insert(std::pair<int,std::string>(std::stoi(frame),line));
                }
            }

            std::pair<int,std::string> File::getSubLine(int frame)
            {
                auto it = _subs.lower_bound(frame);
                if (it != _subs.end())
                {
                    return *it;
                }
                else
                {
                    return std::pair<int,std::string>(999999, "");
                }
            }
        }
    }
}
