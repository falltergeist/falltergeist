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

#ifndef FALLTERGEIST_STATE_START_H
#define FALLTERGEIST_STATE_START_H

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class GameBootingState : public State
        {
            public:
                GameBootingState();
                ~GameBootingState() override;

                void think() override;
                void init() override;

            protected:
                unsigned int _splashTicks = 0;
        };
    }
}
#endif // FALLTERGEIST_START_START_H
