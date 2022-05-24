#pragma once

// Project includes
#include "../../Format/Ini/Value.h"
#include "../../Format/Txt/Parser.h"

// Third-party includes

// stdlib
#include <memory>
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            class File;
            class Value;

            /**
             * @brief Parser of INI files.
             * Parses INI-like TXT files, such as MAPS.TXT, CITY.TXT, etc.
             */
            class Parser : public Txt::Parser
            {
                public:
                    Parser(std::istream &stream);
                    ~Parser();

                    std::unique_ptr<File> parse();

                    static Array parseArray(const std::string& value);

                private:
                    std::istream &_stream; // stream to parse
                    std::string  _section; // current section

                protected:
                    void _stripComments(std::string& line);
            };
        }
    }
}
