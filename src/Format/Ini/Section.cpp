/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 Falltergeist Developers
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

#include "../Ini/Section.h"

#include <functional>

namespace Falltergeist
{
namespace Format
{
namespace Ini
{

Section::Section(const std::string &name) : _name(name)
{
}

Section::~Section()
{
}

const std::string& Section::name() const
{
    return _name;
}

Section::PropertyMap& Section::properties()
{
    return _properties;
}

bool Section::hasProperty(const std::string &name) const
{
    return _properties.find(name) != _properties.end();
}

const Value& Section::property(const std::string& name) const
{
    return _properties.at(name);
}

Value& Section::operator [] (const std::string& name)
{
    return _properties[name];
}

void Section::setProperty(const std::string& name, const Value& value)
{
    _properties[name] = value;
}

std::string Section::propertyString(const std::string &name, const std::string &def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.str();
}

int Section::propertyInt(const std::string &name, int def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.toInt();
}

double Section::propertyDouble(const std::string &name, double def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.toDouble();
}

bool Section::propertyBool(const std::string &name, bool def) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    }
    return iter->second.toBool();
}

Array Section::propertyArray(const std::string& name) const
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter != _properties.end())
    {
        return iter->second.toArray();
    }
    return Array();
}

Section::PropertyRefs Section::listByMask(const std::string& mask, unsigned int start) const
{
    PropertyRefs vec;
    int i = start;
    char key[100];
    snprintf(key, 100, mask.c_str(), i);
    while (hasProperty(key))
    {
        vec.push_back(std::cref(property(key)));
        snprintf(key, 100, mask.c_str(), ++i);
    }
    return vec;
}

Section::iterator Section::begin()
{
    return _properties.begin();
}

Section::const_iterator Section::begin() const
{
    return _properties.begin();
}

Section::iterator Section::end()
{
    return _properties.end();
}

Section::const_iterator Section::end() const
{
    return _properties.end();
}

}
}
}
