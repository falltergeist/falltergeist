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
        std::vector<std::shared_ptr<Object>>* LocationElevation::objects()
        {
            return &_objects;
        }
    }
}
