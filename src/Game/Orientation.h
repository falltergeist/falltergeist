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
#ifndef FALLTERGEIST_GAME_ORIENTATION_H
#define FALLTERGEIST_GAME_ORIENTATION_H

namespace Falltergeist
{
    namespace Game
    {
        /**
         * represents orientation in hexagonal space
         */
        class Orientation
        {
            public:
                enum
                {
                    NS = 0, EW, NC, SC, EC, WC
                };

                Orientation(unsigned char value = NS);
                Orientation& operator =(unsigned char value);
                operator unsigned char() const;

            private:
                unsigned char _dir;
        };
    }
}

#endif //FALLTERGEIST_GAME_ORIENTATION_H
