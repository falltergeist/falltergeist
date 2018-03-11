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

#ifndef FALLTERGEIST_GAME_EXITMISCOBJECT_H
#define FALLTERGEIST_GAME_EXITMISCOBJECT_H

#include "../Game/MiscObject.h"

namespace Falltergeist
{
    namespace Game
    {
        class ExitMiscObject : public MiscObject
        {
            public:
                ExitMiscObject();
                ~ExitMiscObject() override = default;

                int exitHexagonNumber() const;
                void setExitHexagonNumber(int value);

                int exitElevationNumber() const;
                void setExitElevationNumber(int value);

                int exitDirection() const;
                void setExitDirection(int value);

                int exitMapNumber() const;
                void setExitMapNumber(int value);

            protected:
                int _exitHexagonNumber = 0;
                int _exitElevationNumber = 0;
                int _exitDirection = 0;
                int _exitMapNumber = 0;
        };
    }
}
#endif // FALLTERGEIST_GAME_EXITMISCOBJECT_H
