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

#ifndef FALLTERGEIST_GAME_LOCATION_H
#define FALLTERGEIST_GAME_LOCATION_H

// C++ standard includes
#include <map>
#include <string>
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Game
{
class LocationElevation;

/**
 * @brief Location class
 *
 * This class represents world map locations
 * It combines properties from MAPS.TXT and *.map files
 * It also has Game::LocationElevation instancess as its childs
 */
class Location
{
public:
    Location();
    ~Location();

    std::string name() const;
    void setName(const std::string& value);

    std::string filename() const;
    void setFilename(const std::string& value);

    std::string music() const;
    void setMusic(const std::string& value);

    std::map<std::string, unsigned int>* ambientSounds();

    bool saveable() const;
    void setSaveable(bool value);

    bool removeBodies() const;
    void setRemoveBodies(bool value);

    bool pipboyAllowed() const;
    void setPipboyAllowed(bool value);

    std::map<unsigned int, unsigned int>* startPoints();

    std::vector<Game::LocationElevation*>* elevations();

protected:
    /**
     * @brief Location name
     * As defined by `lookup_name` in MAPS.TXT
     */
    std::string _name;

    /**
     * @brief Location filename
     * As defined by `map_name` in MAPS.TXT
     */
    std::string _filename;

    /**
     * @brief Background music file name
     * As defined by `music` in MAPS.TXT
     */
    std::string _music;

    /**
     * @brief ambient sounds in location.
     * As defined by ambiend_sfx in MAPS.TXT
     * std::string - sound file name
     * unsigned int - probability
     */
    std::map<std::string, unsigned int> _ambientSounds;

    /**
     * @brief Save location?
     * As defined by `saved` in MAPS.TXT
     * F.e.: it must be `false` for random encounters
     */
    bool _saveable = false;

    /**
     * @brief Remove dead bodies when player left location?
     * As defined by `dead_bodies_age` in MAPS.TXT
     */
    bool _removeBodies = false;

    /**
     * @brief  Is pipboy accessible in this location?
     * Not defined in MAPS.TXT
     * It changes by game scripts
     */
    bool _pipboyAllowed = true;

    /**
     * @brief Random start points
     * As defined by `random_start_point_*` in MAPS.TXT
     * unsigned int - elevation number
     * unsigned int - hexagon number
     */
    std::map<unsigned int, unsigned int> _startPoints;

    /**
     * @brief Map elevations
     */
    std::vector<Game::LocationElevation*> _elevations;
};

}
}
#endif // FALLTERGEIST_GAME_LOCATION_H
