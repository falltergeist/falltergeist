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
 */

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../../Engine/Exception.h"
#include "../../Engine/Settings/IniFile.h"

// Third party includes

namespace Falltergeist
{

std::shared_ptr<IniSection> IniFile::section(const std::string &name)
{
    auto it = _sections.find(name);
    if (it == _sections.end())
    {
        auto result = std::shared_ptr<IniSection>(new IniSection(name));
        _sections[name] = result;
        return result;
    }
    return it->second;
}

bool IniFile::hasSection(const std::string &name) const
{
    return _sections.find(name) != _sections.end();
}

IniFile::IniFile()
{}

IniFile::~IniFile()
{}

IniFile::iterator IniFile::begin()
{
    return _sections.begin();
}

IniFile::const_iterator IniFile::begin() const
{
    return _sections.begin();
}

IniFile::iterator IniFile::end()
{
    return _sections.end();
}

IniFile::const_iterator IniFile::end() const
{
    return _sections.end();
}

}
