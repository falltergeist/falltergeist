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

// C++ standard includes
#include <algorithm>
#include <functional>
#include <cctype>

// Falltergeist includes
#include "../Dat/Stream.h"
#include "../Lst/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Lst
{

File::File(Dat::Stream&& stream)
{
    stream.setPosition(0);

    std::string line;
    unsigned char ch;
    for (unsigned int i = 0; i != stream.size(); ++i)
    {
        stream >> ch;
        if (ch == 0x0D) // \r
        {
            // do nothing
        }
        else if (ch == 0x0A) // \n
        {
            _addString(line);
            line.clear();
        }
        else
        {
            line += ch;
        }
    }
    if (line.size() != 0)
    {
        _addString(line);
    }
}

void File::_addString(std::string line)
{
    // strip comments
    if (auto pos = line.find(";")) line = line.substr(0, pos);

    // rtrim
    line.erase(std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());

    // replace slashes
    std::replace(line.begin(),line.end(),'\\','/');

    // to lower
    std::transform(line.begin(),line.end(),line.begin(), ::tolower);

    _strings.push_back(line);
}

std::vector<std::string>* File::strings()
{
    return &_strings;
}

}
}
}
