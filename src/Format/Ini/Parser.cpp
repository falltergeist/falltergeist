// Project includes
#include "../Ini/File.h"
#include "../Ini/Parser.h"

// Third-party includes

// stdlib
#include <algorithm>
#include <sstream>

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            Parser::Parser(std::istream &stream) : _stream(stream), _section("")
            {
            }

            Parser::~Parser()
            {
            }

            Array Parser::parseArray(const std::string& str)
            {
                Array ret;
                for (std::string& value : Parser::split(',', str))
                {
                    std::string key = "";
                    Parser::trim(value);
                    // skip empty values
                    if (value.size() == 0)
                    {
                        continue;
                    }
                    // check for associative
                    size_t colon = value.find(':');
                    if (colon != std::string::npos)
                    {
                        key = value.substr(0, colon);
                        Parser::rtrim(key);
                        value = value.substr(colon + 1);
                        Parser::ltrim(value);
                    }
                    if (value.size() > 0)
                    {
                        ret.push_back(std::make_pair(key, value));
                    }
                }
                return ret;
            }

            void Parser::_stripComments(std::string& line)
            {
                auto pos = line.find(";");
                if (pos != std::string::npos)
                {
                    line.erase(pos);
                }
            }

            std::unique_ptr<File> Parser::parse()
            {
                auto ini = std::unique_ptr<File>(new File());
                std::string line;

                while (std::getline(_stream, line))
                {
                    // Lines starting with "#" or ";" are treated as comments and ignored
                    if (line[0] == '#' || line[0] == ';') {
                        continue;
                    }

                    // Prepare line
                    _stripComments(line);
                    trim(line);

                    // Skip empty lines
                    if (line.length() == 0) {
                        continue;
                    }

                    // Found section
                    if (*line.begin() == '[' && *line.rbegin() == ']')
                    {
                        _section = line.substr(1, line.length() - 2);

                        continue;
                    }

                    auto eqPos = line.find('=');
                    if (eqPos == std::string::npos)
                    {
                        continue;
                    }

                    auto name  = line.substr(0, eqPos);
                    auto value = line.substr(eqPos + 1);
                    rtrim(name);
                    ltrim(value);

                    // Property names are case-insensitive
                    toLower(name);

                    ini->section(_section).setProperty(name, value);
                }

                return ini;
            }
        }
    }
}
