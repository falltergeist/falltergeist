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

#ifndef FALLTERGEIST_GAME_SCENERYOBJECT_H
#define FALLTERGEIST_GAME_SCENERYOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/Object.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

/**
 * Stationary object used as scenery.
 */
class SceneryObject : public Object
{
public:
    enum class Subtype
    {
        DOOR = 0,
        STAIRS,
        ELEVATOR,
        LADDER,
        GENERIC
    };

    SceneryObject();
    ~SceneryObject() override;

    char soundId() const;
    void setSoundId(char soundId);

protected:
    char _soundId = 0;
    Subtype _subtype;
};

}
}
#endif // FALLTERGEIST_GAME_SCENERYOBJECT_H
