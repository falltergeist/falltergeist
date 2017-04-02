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

// Falltergeist includes
#include "../../Exception.h"
#include "../Dat/Stream.h"
#include "../Sve/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Sve
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
    auto pos = line.find(":");
    if (pos != std::string::npos)
    {
        auto frame = line.substr(0, pos);
        line = line.substr(pos+1);
        _subs.insert(std::pair<int,std::string>(std::stoi(frame),line));
    }
}

std::pair<int,std::string> File::getSubLine(int frame)
{
    auto it = _subs.lower_bound(frame);
    if (it != _subs.end()) 
    {
        return *it;
    }
    else
    {
        return std::pair<int,std::string>(999999, "");
    }
}

}
}
}
