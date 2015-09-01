/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include "../Game/Location.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Game
{

Location::Location()
{
}

Location::~Location()
{
}

std::string Location::name()
{
    return _name;
}

void Location::setName(const std::string& value)
{
    _name = value;
}

std::string Location::filename()
{
    return _filename;
}

void Location::setFilename(const std::string& value)
{
    _filename = value;
}

std::string Location::music()
{
    return _music;
}

void Location::setMusic(const std::string& value)
{
    _music = value;
}

std::map<std::string, unsigned int>* Location::ambient()
{
    return &_ambient;
}

bool Location::saveable()
{
    return _saveable;
}

void Location::setSaveable(bool value)
{
    _saveable = value;
}

bool Location::removeBodies()
{
    return _removeBodies;
}

void Location::setRemoveBodies(bool value)
{
    _removeBodies = value;
}

bool Location::pipboy()
{
    return _pipboy;
}

void Location::setPipboy(bool value)
{
    _pipboy = value;
}

std::map<unsigned int, unsigned int>* Location::startPoints()
{
    return &_startPoints;
}

}
}
