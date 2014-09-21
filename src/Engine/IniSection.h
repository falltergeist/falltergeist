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
    std::string _name;

    static void _property(PropertyMapConstIterator iter, double &ret, double def);

    static void _property(PropertyMapConstIterator iter, int &ret, int def);

    static void _property(PropertyMapConstIterator iter, bool &ret, bool def);

    static void _property(PropertyMapConstIterator iter, std::string &ret, const std::string &def);

    static bool _hasType(PropertyMapConstIterator iter, IniValue::Tag tag);

    static const char * _tagToString(IniValue::Tag tag);

    static std::string _valueToString(const IniValue &value);

public:
    IniSection(const std::string &name);
    ~IniSection();


    using iterator = PropertyMap::iterator;
    using const_iterator = PropertyMap::const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    int propertyInt(const std::string &name, int def);

    double propertyDouble(const std::string &name, double def);

    bool propertyBool(const std::string &name, bool def);

    std::string propertyString(const std::string &name, const std::string &def);

    void setPropertyInt(const std::string &name, int value);

    void setPropertyDouble(const std::string &name, double value);

    void setPropertyBool(const std::string &name, bool value);

    void setPropertyString(const std::string &name, const std::string &value);

    bool hasProperty(const std::string &name) const;
};

}

#endif // FALLTERGEIST_INI_SECTION_H