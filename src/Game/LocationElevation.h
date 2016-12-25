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

#ifndef FALLTERGEIST_GAME_LOCATIONELEVATION_H
#define FALLTERGEIST_GAME_LOCATIONELEVATION_H

// C++ standard includes
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        class Object;

        /**
         * @brief Location elevation class
         *
         * This class represents each elevation of game location
         * It contains information about tiles and game objects
         */
        class LocationElevation
        {
            public:
                LocationElevation();
                ~LocationElevation();

                bool canRestHere() const;
                void setCanRestHere(bool value);

                std::vector<unsigned>* floorTiles();
                std::vector<unsigned>* roofTiles();
                std::vector<Game::Object*>* objects();

            protected:
                /**
                 * @brief Can player rest here?
                 * As defined by `can_rest_here` in MAPS.TXT
                 */
                bool _canRestHere = true;

                /**
                 * @brief Array of ids of floor tiles
                 */
                std::vector<unsigned> _floorTiles;

                /**
                 * @brief Array of ids of roof tiles
                 */
                std::vector<unsigned> _roofTiles;

                /**
                 * @brief Array of game objects
                 */
                std::vector<Game::Object*> _objects;
        };
    }
}
#endif // FALLTERGEIST_GAME_LOCATIONELEVATION_H
