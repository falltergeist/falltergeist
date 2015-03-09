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

// Falltergeist includes
#include "ExitMiscObject.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameExitMiscObject::GameExitMiscObject()
{
}

int GameExitMiscObject::exitMapNumber() const
{
    return _exitMapNumber;
}

void GameExitMiscObject::setExitMapNumber(int value)
{
    _exitMapNumber = value;
}

int GameExitMiscObject::exitElevationNumber() const
{
    return _exitElevationNumber;
}

void GameExitMiscObject::setExitElevationNumber(int value)
{
    _exitElevationNumber = value;
}

int GameExitMiscObject::exitHexagonNumber() const
{
    return _exitHexagonNumber;
}

void GameExitMiscObject::setExitHexagonNumber(int value)
{
    _exitHexagonNumber = value;
}

int GameExitMiscObject::exitDirection() const
{
    return _exitDirection;
}

void GameExitMiscObject::setExitDirection(int value)
{
    _exitDirection = value;
}

}
}
