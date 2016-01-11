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

#ifndef FALLTERGEIST_FORMAT_INI_VALUE_H
#define FALLTERGEIST_FORMAT_INI_VALUE_H

// C++ standard includes
#include <ostream>
#include <string>

// Libfalltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Ini
{

class Value;

typedef std::vector<std::pair<std::string, Value>> Array;

/**
 * @brief A value in INI file.
 * A wrapper for std::string with conversion functions to various types.
 */
class Value
{
public:
    Value(const std::string &value = "");

    void operator =(const std::string&);

    /*template <class T>
    explicit operator T() const;*/

    operator std::string() const;

    const std::string& str() const;

    int toInt() const;

    double toDouble() const;

    bool toBool() const;

    Array toArray() const;


private:
    std::string _value;

};

inline std::ostream& operator <<(std::ostream& stream, const Value& value)
{
    stream << value.str();
    return stream;
}

}
}
}
#endif // FALLTERGEIST_FORMAT_INI_VALUE_H
