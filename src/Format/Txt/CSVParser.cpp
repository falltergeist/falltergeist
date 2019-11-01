#include <algorithm>
#include <sstream>
#include "CSVParser.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Txt
        {
            CSVParser::CSVParser(std::istream &stream) : _stream(stream)
            {
            }

            CSVParser::~CSVParser()
            {
            }


            void CSVParser::_stripComments(std::string& line)
            {
                size_t pos = line.find(";"), pos2 = line.find("#");
                if (pos != std::string::npos)
                {
                    if (pos2 != std::string::npos)
                    {
                        line.erase(std::min(pos, pos2));
                    }
                    else
                    {
                        line.erase(pos);
                    }
                }
                else if (pos2 != std::string::npos)
                {
                    line.erase(pos2);
                }
            }

            std::unique_ptr<CSVFile> CSVParser::parse()
            {
                auto csv = std::unique_ptr<CSVFile>(new CSVFile());
                std::string line;

                while (std::getline(_stream, line))
                {
                    // Lines starting with "#" or ";" are treated as comments and ignored
                    if (line[0] == '#' || line[0] == ';') continue;

                    // Prepare line
                    _stripComments(line);
                    trim(line);

                    // Skip empty lines
                    if (line.length() == 0) continue;

                    std::vector<Ini::Value> values;
                    auto splitLine = split(',', line);

                    // trim and copy values
                    for (auto& val : splitLine)
                    {
                        trim(val);
                        values.push_back(val);
                    }

                    csv->push_back(std::move(values));
                }

                return csv;
            }
        }
    }
}
