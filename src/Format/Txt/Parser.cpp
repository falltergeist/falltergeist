#include <algorithm>
#include <functional>
#include "../Txt/Parser.h"

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
                line.erase(find_if(line.rbegin(), line.rend(), std::not_fn(::isspace)).base(), line.end());
            }

            void Parser::ltrim(std::string& line)
            {
                line.erase(line.begin(), find_if(line.begin(), line.end(), std::not_fn(::isspace)));
            }

            void Parser::toLower(std::string& line)
            {
                std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            }
        }
    }
}
