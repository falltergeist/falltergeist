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
#include "../Game/Location.h"

// C++ standard includes

// Falltergeist includes
#include "../Format/Gam/File.h"
#include "../Format/Map/File.h"
#include "../Game/LocationElevation.h"
#include "../ResourceManager.h"

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        Location::Location()
        {
        }

        Location::~Location()
        {
        }

        void Location::loadFromMapFile(Falltergeist::Format::Map::File* mapFile)
        {
            setName(mapFile->name().substr(0, mapFile->name().find(".")));
            setDefaultElevationIndex(mapFile->defaultElevation());
            setDefaultPosition(mapFile->defaultPosition());
            setDefaultOrientation(mapFile->defaultOrientation());
            
            // Initialize MAP vars
            if (mapFile->MVARS().size() > 0)
            {
                auto gam = ResourceManager::getInstance()->gamFileType("maps/" + name() + ".gam");
                if (gam)
                {
                    for (auto mvar : *gam->MVARS())
                    {
                        _MVARS.push_back(mvar.second);
                    }
                }
            }
        }
        
        std::vector<int32_t>* Location::MVARS()
        {
            return &_MVARS;
        }
        
        /**
         * @brief Returns location name
         * @return Location name
         */
        std::string Location::name() const
        {
            return _name;
        }

        /**
         * @brief Sets location name
         * @param value Location name
         */
        void Location::setName(const std::string& value)
        {
            _name = value;
        }

        /**
         * @brief Returns location *.map filename
         * @return *.map filename
         */
        std::string Location::filename() const
        {
            return _filename;
        }

        /**
         * @brief Sets *.map filename
         * @param value *.map filename
         */
        void Location::setFilename(const std::string& value)
        {
            _filename = value;
        }

        /**
         * @brief Returns background music filename
         * @return Music filename
         */
        std::string Location::music() const
        {
            return _music;
        }

        /**
         * @brief Sets background music filename
         * @param value Music filename
         */
        void Location::setMusic(const std::string& value)
        {
            _music = value;
        }

        /**
         * @brief Returns ambient sounds map
         * std::string - sound filename
         * unsigned int - probability
         * @return Sounds map
         */
        std::map<std::string, unsigned int>* Location::ambientSounds()
        {
            return &_ambientSounds;
        }

        /**
         * @brief Returns if location need to be saved
         * @return bool
         */
        bool Location::saveable() const
        {
            return _saveable;
        }

        /**
         * @brief Sets if location need to be saved
         * @param value
         */
        void Location::setSaveable(bool value)
        {
            _saveable = value;
        }

        /**
         * @brief Returns if dead bodies should be removed when player leave location
         * @return bool
         */
        bool Location::removeBodies() const
        {
            return _removeBodies;
        }

        /**
         * @brief Sets if dead bodies should be removed when player leave location
         * @param value
         */
        void Location::setRemoveBodies(bool value)
        {
            _removeBodies = value;
        }

        /**
         * @brief Returns if pipboy is allowed in this location
         * @return bool
         */
        bool Location::pipboyAllowed() const
        {
            return _pipboyAllowed;
        }

        /**
         * @brief Sets if pipboy is allowed in this location
         * @param value
         */
        void Location::setPipboyAllowed(bool value)
        {
            _pipboyAllowed = value;
        }

        /**
         * @brief Returns map of start points
         * unsigned int - elevation number
         * unsigned int - hexagon number
         * @return Start points
         */
        std::map<unsigned int, unsigned int>* Location::startPoints()
        {
            return &_startPoints;
        }

        /**
         * @brief Returns index of default elevation
         * @return Index of default elevation
         */
        unsigned int Location::defaultElevationIndex() const
        {
            return _defaultElevationIndex;
        }
        
        /**
         * Sets index of default elevation
         * @param value
         */
        void Location::setDefaultElevationIndex(unsigned int value)
        {
            _defaultElevationIndex = value;
        }
        
        /**
         * @brief Returns default position on default elevation
         * @return Default position on default elevation 
         */
        unsigned int Location::defaultPosition() const
        {
            return _defaultPosition;
        }
        
        /**
         * Sets default position on default elevation
         * @param value
         */
        void Location::setDefaultPosition(unsigned int value)
        {
            _defaultPosition = value;
        }
        
        /**
         * @brief Returns default orientation on default elevation
         * @return Default orientation on default elevation
         */
        unsigned int Location::defaultOrientation() const
        {
            return _defaultOrientation;
        }
        
        /**
         * Sets default orientation on default elevation
         * @param value
         */
        void Location::setDefaultOrientation(unsigned int value)
        {
            _defaultOrientation = value;
        }        
        
        /**
         * @brief Returns location elevations
         * @return Elevations
         */
        std::vector<LocationElevation*>* Location::elevations()
        {
            return &_elevations;
        }
    }
}