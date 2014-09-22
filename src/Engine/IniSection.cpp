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
#include "../Engine/Logger.h"

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

void IniSection::_property(PropertyMapConstIterator iter, std::string &ret, const std::string &def)
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
    Logger::warning("[INI]")
            << "Property `" << iter->first
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

void IniSection::setPropertyInt(const std::string &name, int value)
{
    _properties[name] = IniValue(value);
}

void IniSection::setPropertyDouble(const std::string &name, double value)
{
    _properties[name] = IniValue(value);
}

void IniSection::setPropertyBool(const std::string &name, bool value)
{
    _properties[name] = IniValue(value);
}

void IniSection::setPropertyString(const std::string &name, const std::string &value)
{
    _properties[name] = IniValue(value);
}

bool IniSection::hasProperty(const std::string &name) const
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

int IniSection::propertyInt(const std::string &name, int def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        Logger::warning("[INI]") << "Property `" << name << "` not found, use default value: " << def << std::endl;
        return def;
    };
    int ret;
    IniSection::_property(iter, ret, def);
    return ret;
}

double IniSection::propertyDouble(const std::string &name, double def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        Logger::warning("[INI]") << "Property `" << name << "` not found, use default value: " << def << std::endl;
        return def;
    };
    double ret;
    IniSection::_property(iter, ret, def);
    return ret;
}

bool IniSection::propertyBool(const std::string &name, bool def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        Logger::warning("[INI]") << "Property `" << name << "` not found, use default value: " << def << std::endl;
        return def;
    };
    bool ret;
    IniSection::_property(iter, ret, def);
    return ret;
}

std::string IniSection::propertyString(const std::string &name, const std::string &def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        Logger::warning("[INI]") << "Property `" << name << "` not found, use default value: " << def << std::endl;
        return def;
    };
    std::string ret;
    IniSection::_property(iter, ret, def);
    return ret;
}

IniSection::IniSection(const std::string &name) : _name(name)
{
}

IniSection::~IniSection()
{

}

IniSection::iterator IniSection::begin()
{
    return _properties.begin();
}

IniSection::const_iterator IniSection::begin() const
{
    return _properties.begin();
}

IniSection::iterator IniSection::end()
{
    return _properties.end();
}

IniSection::const_iterator IniSection::end() const
{
    return _properties.end();
}

}
