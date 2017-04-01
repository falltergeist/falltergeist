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
#include "../Ini/Value.h"

// C++ standard includes
#include <sstream>
#include <algorithm>

// Falltergeist includes
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Ini
{

Value::Value(const std::string& value) : _value(value)
{
}

void Value::operator =(const std::string& value)
{
    _value = value;
}

Value::operator std::string() const
{
    return _value;
}

const std::string& Value::str() const
{
    return _value;
}

/*template<class T>
explicit Value::operator T() const
{
    T ret;
    std::istringstream stream(_value);
    stream >> ret;
    return ret;
}*/

int Value::toInt() const
{
    try
    {
        return std::stoi(_value);
    }
    catch (const std::invalid_argument&)
    {
        return 0;
    }
}

double Value::toDouble() const
{
    try
    {
        return std::stod(_value);
    }
    catch (const std::invalid_argument&)
    {
        return 0.0;
    }
}

bool Value::toBool() const
{
    std::string lc = _value;
    Parser::toLower(lc);
    return (lc == "on" || lc == "true");
}

Array Value::toArray() const
{
    return Parser::parseArray(_value);
}

}
}
}
