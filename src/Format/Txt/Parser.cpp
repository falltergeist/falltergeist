// Project includes
#include "../Txt/Parser.h"

// Third-party includes

// stdlib
#include <algorithm>
#include <functional>

namespace Falltergeist
{
    namespace Format
    {
        namespace Txt
        {
            std::vector<std::string> Parser::split(char delim, const std::string& source)
            {
                std::vector<std::string> tokens;
                size_t start = 0, end = 0;
                while ((end = source.find(delim, start)) != std::string::npos)
                {
                    tokens.push_back(source.substr(start, end - start));
                    start = end + 1;
                }
                tokens.push_back(source.substr(start));
                return tokens;
            }

            void Parser::trim(std::string& line)
            {
                ltrim(line);
                rtrim(line);
            }

            void Parser::rtrim(std::string& line)
            {
                line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char c) {
                    return !std::isspace(c);
                }).base(), line.end());
            }

            void Parser::ltrim(std::string& line)
            {
                line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char c) {
                    return !std::isspace(c);
                }));
            }

            void Parser::toLower(std::string& line)
            {
                std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            }
        }
    }
}
