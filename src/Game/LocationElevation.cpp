// Project includes
#include "../Game/LocationElevation.h"
#include "../UI/TileMap.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        LocationElevation::LocationElevation(std::shared_ptr<ILogger> logger)
        {
            this->logger = std::move(logger);
            _roof = std::make_shared<UI::TileMap>(this->logger);
            _floor = std::make_shared<UI::TileMap>(this->logger);
        }

        LocationElevation::~LocationElevation()
        {
        }

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
