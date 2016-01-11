/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
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

// Related headers
#include "../Ini/Parser.h"

// C++ standard includes
#include <algorithm>
#include <sstream>

// Falltergeist includes
#include "../Ini/File.h"

// Third party includes

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
        if (line[0] == '#' || line[0] == ';') continue;

        // Prepare line
        _stripComments(line);
        trim(line);

        // Skip empty lines
        if (line.length() == 0) continue;

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
