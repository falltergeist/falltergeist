#pragma once

// Project includes

// Third-party includes

// stdlib
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Txt
        {
            /**
             * @brief Base class for text file parsers with some helper functions.
             */
            class Parser
            {
                public:
                    static std::vector<std::string> split(char delim, const std::string& source);

                    static void trim(std::string& value);

                    static void rtrim(std::string& value);

                    static void ltrim(std::string& value);

                    static void toLower(std::string& value);
            };
        }
    }
}
