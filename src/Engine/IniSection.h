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

#ifndef FALLTERGEIST_INI_SECTION_H
#define FALLTERGEIST_INI_SECTION_H

// C++ standard includes
#include <iostream>
#include <map>
#include <string>

// Falltergeist includes

#include "../Engine/IniValue.h"

// Third party includes

namespace Falltergeist
{

class IniSection
{
private:
    using PropertyMap = std::map<std::string, IniValue>;
    using PropertyMapConstIterator = PropertyMap::const_iterator;

    PropertyMap _properties;

    static void _property(PropertyMapConstIterator iter, double &ret, double def);

    static void _property(PropertyMapConstIterator iter, int &ret, int def);

    static void _property(PropertyMapConstIterator iter, bool &ret, bool def);

    static void _property(PropertyMapConstIterator iter, std::string &ret, std::string def);

    static bool _hasType(PropertyMapConstIterator iter, IniValue::Tag tag);

    static const char * _tagToString(IniValue::Tag tag);

    static std::string _valueToString(const IniValue &value);

public:
    template <class T>
    T property(std::string name, const T& def)
    {
        PropertyMapConstIterator iter = _properties.find(name);
        if (iter == _properties.end())
        {
            std::cerr << "Property `" << name << "` not found, use default value: " << def << std::endl;
            return def;
        };

        T ret;
        IniSection::_property(iter, ret, def);
        return ret;
    }

    void setProperty(std::string name, int value);

    void setProperty(std::string name, double value);

    void setProperty(std::string name, bool value);

    void setProperty(std::string name, const std::string &value);

    bool hasProperty(std::string name) const;
};

}

#endif // FALLTERGEIST_INI_SECTION_H