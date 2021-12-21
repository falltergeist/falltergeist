#include <vector>
#include <algorithm>
#include <cctype>
#include "../../Exception.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Gam/File.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Gam
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);

                unsigned int i = 0;
                unsigned char ch;
                std::string line;
                while (i != stream.size())
                {
                    stream >> ch;
                    i++;
                    if (ch != 0x0D) // \r
                    {
                        line += ch;
                    }
                    else
                    {
                        stream.skipBytes(1);
                        i++; // 0x0A \n
                        _parseLine(line);
                        line.clear();
                    }
                }
                if (line.length() != 0)
                {
                    _parseLine(line);
                }
            }

            void File::_parseLine(std::string line)
            {
                // cut everything after comment
                if (line.find("//") != std::string::npos)
                {
                    line = line.substr(0, line.find("//"));
                }

                // rtrim
                line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char c) {
                    return !std::isspace(c);
                }).base(), line.end());

                if (line.length() == 0) return;

                if (line == "GAME_GLOBAL_VARS:")
                {
                    _GVARmode = true;
                    return;
                }
                if (line == "MAP_GLOBAL_VARS:")
                {
                    _MVARmode = true;
                    return;
                }

                std::string name = line.substr(0, line.find(":="));
                std::string value = line.substr(line.find(":=")+2,line.find(";")-line.find(":=")-2);
                // rtrim
                name.erase(std::find_if(name.rbegin(), name.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), name.end());

//                name.erase(std::find_if(name.rbegin(), name.rend(), [](unsigned char c) {
//                    return std::isspace(c);
//                }).base(), name.end());

                if (_GVARmode)
                {
                    _GVARS.insert(std::make_pair(name, std::stoi(value)));
                    return;
                }
                else if(_MVARmode)
                {
                    _MVARS.insert(std::make_pair(name, std::stoi(value)));
                    return;
                }
                else
                {
                    throw Exception("File::_parseLine() - unknown mode");
                }
            }

            std::map<std::string, int>* File::GVARS()
            {
                return &_GVARS;
            }

            std::map<std::string, int>* File::MVARS()
            {
                return &_MVARS;
            }

            int File::GVAR(std::string name)
            {
                if (_GVARS.find(name) != _GVARS.end())
                {
                    return _GVARS.at(name);
                }
                throw Exception("File::GVAR(name) - GVAR not found:" + name);
            }

            int File::MVAR(std::string name)
            {
                if (_MVARS.find(name) != _MVARS.end())
                {
                    return _MVARS.at(name);
                }
                throw Exception("File::MVAR(name) - MVAR not found:" + name);
            }

            int File::GVAR(unsigned int number)
            {
                unsigned int i = 0;
                for (auto gvar : _GVARS)
                {
                    if (i == number) return gvar.second;
                    i++;
                }
                throw Exception("File::GVAR(number) - not found: " + std::to_string(number));
            }

            int File::MVAR(unsigned int number)
            {
                unsigned int i = 0;
                for (auto mvar : _MVARS)
                {
                    if (i == number) return mvar.second;
                    i++;
                }
                throw Exception("File::MVAR(number) - not found: " + std::to_string(number));
            }
        }
    }
}
