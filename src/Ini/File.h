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

#ifndef FALLTERGEIST_ENGINE_INI_FILE_H
#define	FALLTERGEIST_ENGINE_INI_FILE_H

// C++ standard includes
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <algorithm>

// Falltergeist includes
#include "../Ini/Parser.h"
#include "../Ini/Section.h"

// Third party includes

namespace Falltergeist
{
namespace Engine
{
namespace Ini
{

class File
{
    std::map<std::string, std::shared_ptr<Section>> _sections;
public:
    using iterator = std::map<std::string, std::shared_ptr<Section>>::iterator;
    using const_iterator = std::map<std::string, std::shared_ptr<Section>>::const_iterator;

    File();
    ~File();
    std::shared_ptr<Section> section(const std::string &name);
    std::map<std::string, std::shared_ptr<Section>>* sections();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    bool hasSection(const std::string &name) const;
};

} // Ini
} // Engine
} // Falltergeist

#endif	// FALLTERGEIST_ENGINE_INI_FILE_H
