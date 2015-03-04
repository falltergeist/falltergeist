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

#ifndef FALLTERGEIST_GAMEEXITMISCOBJECT_H
#define FALLTERGEIST_GAMEEXITMISCOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "MiscObject.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

class GameExitMiscObject : public GameMiscObject
{
protected:
    int _exitHexagonNumber = 0;
    int _exitElevationNumber = 0;
    int _exitDirection = 0;
    int _exitMapNumber = 0;
public:
    GameExitMiscObject();

    int exitHexagonNumber() const;
    void setExitHexagonNumber(int value);

    int exitElevationNumber() const;
    void setExitElevationNumber(int value);

    int exitDirection() const;
    void setExitDirection(int value);

    int exitMapNumber() const;
    void setExitMapNumber(int value);
};

}
}
#endif // FALLTERGEIST_GAMEEXITMISCOBJECT_H
