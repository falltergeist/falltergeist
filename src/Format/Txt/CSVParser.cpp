/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 Falltergeist Developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "CSVParser.h"

#include <algorithm>
#include <sstream>

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
