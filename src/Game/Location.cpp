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

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "Location.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameLocation::GameLocation()
{
}

std::string GameLocation::name()
{
    return _name;
}

void GameLocation::setName(std::string value)
{
    _name = value;
}

std::string GameLocation::filename()
{
    return _filename;
}

void GameLocation::setFilename(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    _filename = value;
}

std::string GameLocation::music()
{
    return _music;
}

void GameLocation::setMusic(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    _music = value;
}

std::map<std::string, unsigned int>* GameLocation::ambient()
{
    return &_ambient;
}

bool GameLocation::saveable()
{
    return _saveable;
}

void GameLocation::setSaveable(bool value)
{
    _saveable = value;
}

bool GameLocation::removeBodies()
{
    return _removeBodies;
}

void GameLocation::setRemoveBodies(bool value)
{
    _removeBodies = value;
}

bool GameLocation::pipboy()
{
    return _pipboy;
}

void GameLocation::setPipboy(bool value)
{
    _pipboy = value;
}

std::map<unsigned int, unsigned int>* GameLocation::startPoints()
{
    return &_startPoints;
}

}
}
