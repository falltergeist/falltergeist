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
#include "../Ini/File.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Ini
{

File::File()
{
}

File::~File()
{
}

Section& File::section(const std::string &name)
{
    auto it = _sectionIdxMap.find(name);
    if (it == _sectionIdxMap.end())
    {
        auto idx = _sections.size();
        _sections.emplace_back(name);
        _sectionIdxMap[name] = idx;
        return _sections.at(idx);
    }
    return _sections.at(it->second);
}

Section& File::operator [] (const std::string &name)
{
    return section(name);
}

bool File::hasSection(const std::string &name) const
{
    return _sectionIdxMap.find(name) != _sectionIdxMap.end();
}

const File::Sections& File::sections()
{
    return _sections;
}

File::iterator File::begin()
{
    return _sections.begin();
}

File::const_iterator File::begin() const
{
    return _sections.begin();
}

File::iterator File::end()
{
    return _sections.end();
}

File::const_iterator File::end() const
{
    return _sections.end();
}

}
}
}
