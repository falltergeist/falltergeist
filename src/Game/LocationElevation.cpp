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

#include "../Game/LocationElevation.h"

#include "../UI/TileMap.h"

namespace Falltergeist
{
    namespace Game
    {
        LocationElevation::LocationElevation()
        {
            _roof = std::make_shared<UI::TileMap>();
            _floor = std::make_shared<UI::TileMap>();
        }

        LocationElevation::~LocationElevation() = default;

        /**
         * @brief Returns if player can rest on this elevation
         * @return bool
         */
        bool LocationElevation::canRestHere() const
        {
            return _canRestHere;
        }

        /**
         * @brief Sets if player can rest on this elevation
         * @param[in] value
         */
        void LocationElevation::setCanRestHere(bool value)
        {
            _canRestHere = value;
        }

        std::shared_ptr<UI::TileMap> LocationElevation::floor()
        {
            return _floor;
        }

        std::shared_ptr<UI::TileMap> LocationElevation::roof()
        {
            return _roof;
        }

        /**
         * @brief Returns array of game objects
         * @return Game objects
         */
        std::vector<Object*>* LocationElevation::objects()
        {
            return &_objects;
        }
    }
}
