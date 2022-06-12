// Project includes
#include "../Game/Location.h"
#include "../Format/Gam/File.h"
#include "../Format/Map/File.h"
#include "../Game/LocationElevation.h"
#include "../Game/SpatialObject.h"
#include "../Helpers/GameObjectHelper.h"
#include "../ResourceManager.h"
#include "../UI/Tile.h"
#include "../UI/TileMap.h"
#include "../VM/Script.h"

// Third-party includes

// stdlib
#include <cmath>

namespace Falltergeist
{
    namespace Game
    {
        Location::Location(std::shared_ptr<ILogger> logger)
        {
            this->logger = std::move(logger);
        }

        Location::~Location()
        {
        }

        void Location::loadFromMapFile(std::unique_ptr<Format::Map::File>& mapFile)
        {
            setName(mapFile->name().substr(0, mapFile->name().find(".")));
            setDefaultElevationIndex(mapFile->defaultElevation());
            setDefaultPosition(mapFile->defaultPosition());
            setDefaultOrientation(mapFile->defaultOrientation());

            // Initialize MAP vars
            if (!mapFile->MVARS().empty()) {
                auto gam = ResourceManager::getInstance()->gamFileType("maps/" + name() + ".gam");
                if (gam) {
                    for (auto mvar : *gam->MVARS()) {
                        _MVARS.push_back(mvar.second);
                    }
                }
            }

            if (mapFile->scriptId() > 0) {
                _script = std::make_shared<VM::Script>(
                    ResourceManager::getInstance()->intFileType((unsigned)mapFile->scriptId() - 1),
                    nullptr
                );
            }

            Helpers::GameObjectHelper gameObjectHelper(logger);

            for (auto &mapElevation : mapFile->elevations()) {
                auto elevation = std::make_shared<LocationElevation>(logger);

                // load objects
                for (auto &mapObject : mapElevation.objects()) {

                    auto object = gameObjectHelper.createFromMapObject(mapObject);
                    if (!object) {
                        // TODO: add some logging
                        continue;
                    }

                    elevation->objects()->push_back(object);
                }

                // load tiles
                for (unsigned int i = 0; i != 100 * 100; ++i) {
                    auto tileX = static_cast<unsigned>(ceil(((double) i) / 100));
                    unsigned int tileY = i % 100;
                    unsigned int x = (100 - tileY - 1) * 48 + 32 * (tileX - 1);
                    unsigned int y = tileX * 24 + (tileY - 1) * 12 + 1;

                    unsigned int tileNum = mapElevation.floorTiles().at(i);
                    if (tileNum > 1) {
                        elevation->floor()->tiles()[i] = std::make_unique<UI::Tile>(tileNum, Graphics::Point(x, y));
                    }

                    tileNum = mapElevation.roofTiles().at(i);
                    if (tileNum > 1) {
                        elevation->roof()->tiles()[i] = std::make_unique<UI::Tile>(tileNum, Graphics::Point(x, y - 96));
                    }
                }

                elevations()->push_back(elevation);
            }

            // load spatial objects(scripts)
            for (auto &script: mapFile->scripts()) {
                if (script.type() == Format::Map::Script::Type::SPATIAL) {
                    auto object = gameObjectHelper.createFromMapSpatialScript(script);
                    elevations()->at(object->elevation())->objects()->push_back(object);
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
        std::vector<std::shared_ptr<LocationElevation>>* Location::elevations()
        {
            return &_elevations;
        }

        std::shared_ptr<VM::Script> Location::script() const
        {
            return _script;
        }
    }
}
