/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/IniValue.h"

// Third party includes

namespace Falltergeist
{

IniValue::IniValue()
{}

IniValue::~IniValue()
{
    using std::string;
    if (_tag == IniValue::Tag::STRING)
    {
        _stringVal.~string();
    }
}

IniValue &IniValue::operator=(const IniValue &rhs)
{
    using std::string;

    if (&rhs == this) return *this;

    _tag = rhs._tag;
    switch (_tag)
    {
        case IniValue::Tag::INTEGER:
            _integerVal = rhs._integerVal;
            break;
        case IniValue::Tag::DOUBLE:
            _doubleVal = rhs._doubleVal;
            break;
        case IniValue::Tag::BOOLEAN:
            _booleanVal = rhs._booleanVal;
            break;
        case IniValue::Tag::STRING:
            new(&_stringVal) std::string(rhs._stringVal);
            break;
    }

    return *this;
}

IniValue::IniValue(double doubleVal) : _tag(IniValue::Tag::DOUBLE), _doubleVal(doubleVal)
{}

IniValue::IniValue(int integerVal) : _tag(IniValue::Tag::INTEGER), _integerVal(integerVal)
{}

IniValue::IniValue(bool booleanVal) : _tag(IniValue::Tag::BOOLEAN), _booleanVal(booleanVal)
{}

IniValue::IniValue(std::string stringVal) : _tag(IniValue::Tag::STRING)
{
    new(&_stringVal) std::string(stringVal);
}

}