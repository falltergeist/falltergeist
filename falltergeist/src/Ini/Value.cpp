/*
 * Copyright 2012-2018 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// Related headers
#include "../Ini/Value.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Ini
{

Value::Value()
{
}

Value::~Value()
{
    using std::string;
    if (_tag == Value::Tag::STRING)
    {
        _stringVal.~string();
    }
    if (_tag == Value::Tag::ARRAY)
    {
        _iniVal.~vector();
    }
}

Value &Value::operator=(const Value &rhs)
{
    using std::string;

    if (&rhs == this) return *this;

    _tag = rhs._tag;
    switch (_tag)
    {
        case Value::Tag::INTEGER:
            _integerVal = rhs._integerVal;
            break;
        case Value::Tag::DOUBLE:
            _doubleVal = rhs._doubleVal;
            break;
        case Value::Tag::BOOLEAN:
            _booleanVal = rhs._booleanVal;
            break;
        case Value::Tag::STRING:
            new(&_stringVal) std::string(rhs._stringVal);
            break;
        case Value::Tag::ARRAY:
            new(&_iniVal) std::vector<Value>(rhs._iniVal);
            break;
    }

    return *this;
}

Value::Value(double doubleVal) : _tag(Value::Tag::DOUBLE), _doubleVal(doubleVal)
{
}

Value::Value(int integerVal) : _tag(Value::Tag::INTEGER), _integerVal(integerVal)
{
}

Value::Value(bool booleanVal) : _tag(Value::Tag::BOOLEAN), _booleanVal(booleanVal)
{
}

Value::Value(const std::string& stringVal) : _tag(Value::Tag::STRING)
{
    new(&_stringVal) std::string(stringVal);
}

Value::Value(std::vector<Value> iniVal) : _tag(Value::Tag::ARRAY)
{
    new(&_iniVal) std::vector<Value>(iniVal);
}

Value::Value(const Value &rhs) : _tag(rhs._tag)
{
    using std::string;

    switch (_tag)
    {
        case Value::Tag::INTEGER:
            _integerVal = rhs._integerVal;
            break;
        case Value::Tag::DOUBLE:
            _doubleVal = rhs._doubleVal;
            break;
        case Value::Tag::BOOLEAN:
            _booleanVal = rhs._booleanVal;
            break;
        case Value::Tag::STRING:
            new(&_stringVal) std::string(rhs._stringVal);
            break;
        case Value::Tag::ARRAY:
            new(&_iniVal) std::vector<Value>(rhs._iniVal);
            break;
    }
}

std::string Value::tagString(Value::Tag tag)
{
    switch (tag)
    {
        case Value::Tag::INTEGER:
            return "integer";
        case Value::Tag::DOUBLE:
            return "double";
        case Value::Tag::BOOLEAN:
            return "bool";
        case Value::Tag::STRING:
            return "string";
        case Value::Tag::ARRAY:
            return "array";
    }

    return "unreachable";
}

std::string Value::value() const
{
    switch (_tag)
    {
        case Value::Tag::INTEGER:
            return std::to_string(_integerVal);
        case Value::Tag::DOUBLE:
            return std::to_string(_doubleVal);
        case Value::Tag::BOOLEAN:
            return _booleanVal ? "true" : "false";
        case Value::Tag::STRING:
            return _stringVal;
        case Value::Tag::ARRAY:
            std::stringstream ss;
            for(size_t i = 0; i < _iniVal.size(); ++i)
            {
                if(i != 0)
                    ss << ",";
                ss << _iniVal[i].value();
            }
            std::string _s = ss.str();
            return _s;
    }

    return "unreachable";
}

int Value::intValue() const
{
    if (_tag == Value::Tag::INTEGER)
    {
        return _integerVal;
    }
    return 0;
}

bool Value::boolValue() const
{
    if (_tag == Value::Tag::BOOLEAN)
    {
        return _booleanVal;
    }
    return false;
}

double Value::doubleValue() const
{
    if (_tag == Value::Tag::DOUBLE)
    {
        return _doubleVal;
    }
    return 0.0;
}

Value::Tag Value::tag() const
{
    return _tag;
}

}
}
