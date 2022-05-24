#pragma once

// Project includes
#include "../Ini/Value.h"
#include "../Txt/Parser.h"

// Third-party includes

// stdlib
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Txt
        {
            typedef std::list<std::vector<Ini::Value>> CSVFile;

            /**
             * @brief Parser of CSV files.
             */
            class CSVParser : public Parser
            {
                public:
                    CSVParser(std::istream &stream);
                    ~CSVParser();

                    std::unique_ptr<CSVFile> parse();

                private:
                    std::istream &_stream; // stream to parse

                protected:
                    void _stripComments(std::string& line);
            };
        }
    }
}
