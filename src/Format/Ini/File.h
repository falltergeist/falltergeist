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

#ifndef FALLTERGEIST_FORMAT_INI_FILE_H
#define FALLTERGEIST_FORMAT_INI_FILE_H

// C++ standard includes
#include <map>
#include <string>
#include <vector>

// Libfalltergeist includes
#include "../Ini/Parser.h"
#include "../Ini/Section.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Ini
{

/**
 * @brief A regular INI file.
 */
class File
{
public:
    using Sections = std::vector<Section>;
    using iterator = Sections::iterator;
    using const_iterator = Sections::const_iterator;

    File();
    ~File();

    /**
     * Returns reference to section with given name. If it's not exist, empty section will be created automatically.
     */
    Section& section(const std::string &name);
    /**
     * An alias for section().
     */
    Section& operator [] (const std::string &name);
    /**
     * Checks if section with given name exists or not.
     */
    bool hasSection(const std::string &name) const;
    /**
     * Returns reference to internal vector of sections.
     */
    const Sections& sections();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    Sections _sections;
    std::map<std::string, size_t> _sectionIdxMap;

};

}
}
}
#endif	// FALLTERGEIST_FORMAT_INI_FILE_H
