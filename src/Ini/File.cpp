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

#include "../Ini/File.h"

namespace Falltergeist
{
namespace Ini
{

File::File()
{
}

File::~File()
{
}

std::shared_ptr<Section> File::section(const std::string &name)
{
    auto it = _sections.find(name);
    if (it == _sections.end())
    {
        auto result = std::shared_ptr<Section>(new Section(name));
        _sections[name] = result;
        return result;
    }
    return it->second;
}

bool File::hasSection(const std::string &name) const
{
    return _sections.find(name) != _sections.end();
}

std::map<std::string, std::shared_ptr<Section>>* File::sections()
{
    return &_sections;
}

File::iterator File::begin()
{
    return _sections.begin();
}

File::const_iterator File::begin() const
{
    return _sections.begin();
}

File::iterator File::end()
{
    return _sections.end();
}

File::const_iterator File::end() const
{
    return _sections.end();
}

}
}
