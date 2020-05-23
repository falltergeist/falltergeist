#pragma once

#include <memory>
#include <vector>

namespace Falltergeist
{
    namespace UI
    {
        class TileMap;
    }
    namespace Game
    {
        class Object;

        /**
         * @brief Location elevation class
         *
         * This class represents each elevation of game location
         * It contains information about tiles and game objects
         */
        class LocationElevation final
        {
            public:
                LocationElevation();
                ~LocationElevation();

                bool canRestHere() const;
                void setCanRestHere(bool value);

                std::shared_ptr<UI::TileMap> floor();
                std::shared_ptr<UI::TileMap> roof();

                std::vector<std::shared_ptr<Object>>* objects();

            protected:
                /**
                 * @brief Can player rest here?
                 * As defined by `can_rest_here` in MAPS.TXT
                 */
                bool _canRestHere = true;

                std::shared_ptr<UI::TileMap> _floor;

                std::shared_ptr<UI::TileMap> _roof;

                /**
                 * @brief Array of game objects
                 */
                std::vector<std::shared_ptr<Object>> _objects;
        };
    }
}
