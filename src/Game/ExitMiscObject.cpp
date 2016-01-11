/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../Game/ExitMiscObject.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Game
{

ExitMiscObject::ExitMiscObject()
{
}

ExitMiscObject::~ExitMiscObject()
{
}

int ExitMiscObject::exitMapNumber() const
{
    return _exitMapNumber;
}

void ExitMiscObject::setExitMapNumber(int value)
{
    _exitMapNumber = value;
}

int ExitMiscObject::exitElevationNumber() const
{
    return _exitElevationNumber;
}

void ExitMiscObject::setExitElevationNumber(int value)
{
    _exitElevationNumber = value;
}

int ExitMiscObject::exitHexagonNumber() const
{
    return _exitHexagonNumber;
}

void ExitMiscObject::setExitHexagonNumber(int value)
{
    _exitHexagonNumber = value;
}

int ExitMiscObject::exitDirection() const
{
    return _exitDirection;
}

void ExitMiscObject::setExitDirection(int value)
{
    _exitDirection = value;
}

}
}
