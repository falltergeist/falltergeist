#pragma once

// Project includes
#include "../ILogger.h"

// Third-party includes

// stdlib
#include <memory>
#include <map>
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            class File;
        }
    }
    namespace VM
    {
        class Script;
    }
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
        class Location final
        {
            public:
                Location(std::shared_ptr<ILogger> logger);
                ~Location();

                void loadFromMapFile(Falltergeist::Format::Map::File *file);

                std::vector<int32_t>* MVARS();

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

                unsigned int defaultElevationIndex() const;
                void setDefaultElevationIndex(unsigned int value);

                unsigned int defaultPosition() const;
                void setDefaultPosition(unsigned int value);

                unsigned int defaultOrientation() const;
                void setDefaultOrientation(unsigned int value);

                std::vector<std::shared_ptr<LocationElevation>>* elevations();

                std::shared_ptr<VM::Script> script() const;

            private:
                std::shared_ptr<ILogger> logger;

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
                 * @brief Index of default elevation
                 */
                unsigned int _defaultElevationIndex = 0;

                /**
                 * @brief Default position on default elevation
                 */
                unsigned int _defaultPosition = 0;

                /**
                 * @brief Default orientation on default elevation
                 */
                unsigned int _defaultOrientation = 0;

                /**
                 * @brief Location variables. Used in scripting
                 */
                std::vector<int32_t> _MVARS;

                /**
                 * @brief Map elevations
                 */
                std::vector<std::shared_ptr<LocationElevation>> _elevations;

                std::shared_ptr<VM::Script> _script;
        };
    }
}
