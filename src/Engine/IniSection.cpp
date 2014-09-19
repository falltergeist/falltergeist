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
#include "../Engine/Exception.h"
#include "../Engine/IniSection.h"

// Third party includes

namespace Falltergeist
{

void IniSection::_property(PropertyMapConstIterator iter, double &ret, double def)
{
    if (!_hasType(iter, IniValue::Tag::DOUBLE))
    {
        ret = def;
        return;
    }

    ret = iter->second._doubleVal;
}

void IniSection::_property(PropertyMapConstIterator iter, int &ret, int def)
{
    if (!_hasType(iter, IniValue::Tag::INTEGER))
    {
        ret = def;
        return;
    }

    ret = iter->second._integerVal;
}

void IniSection::_property(PropertyMapConstIterator iter, bool &ret, bool def)
{
    if (!_hasType(iter, IniValue::Tag::BOOLEAN))
    {
        ret = def;
        return;
    }

    ret = iter->second._booleanVal;
}

void IniSection::_property(PropertyMapConstIterator iter, std::string &ret, std::string def)
{
    if (!_hasType(iter, IniValue::Tag::STRING))
    {
        ret = def;
        return;
    }

    ret = iter->second._stringVal;
}

bool IniSection::_hasType(PropertyMapConstIterator iter, IniValue::Tag tag)
{
    if (iter->second._tag == tag) return true;

    std::cerr << "Property `" << iter->first
            << " `expected to be " << _tagToString(tag)
            << " but " << _tagToString(iter->second._tag)
            << " value encountered: " << _valueToString(iter->second)
            << std::endl;

    return false;
}

const char *IniSection::_tagToString(IniValue::Tag tag)
{
    switch (tag)
    {
        case IniValue::Tag::INTEGER:
            return "integer";
        case IniValue::Tag::DOUBLE:
            return "double";
        case IniValue::Tag::BOOLEAN:
            return "bool";
        case IniValue::Tag::STRING:
            return "string";
    }

    return "unreachable";
}

void IniSection::setProperty(std::string name, int value)
{
    _properties[name] = IniValue(value);
}

void IniSection::setProperty(std::string name, double value)
{
    _properties[name] = IniValue(value);
}

void IniSection::setProperty(std::string name, bool value)
{
    _properties[name] = IniValue(value);
}

void IniSection::setProperty(std::string name, const std::string &value)
{
    _properties[name] = IniValue(value);
}

bool IniSection::hasProperty(std::string name) const
{
    return _properties.find(name) != _properties.end();
}

std::string IniSection::_valueToString(const IniValue &value)
{
    switch (value._tag)
    {
        case IniValue::Tag::INTEGER:
            return std::to_string(value._integerVal);
        case IniValue::Tag::DOUBLE:
            return std::to_string(value._doubleVal);
        case IniValue::Tag::BOOLEAN:
            return std::to_string(value._booleanVal);
        case IniValue::Tag::STRING:
            return value._stringVal;
    }

    return "unreachable";
}
}