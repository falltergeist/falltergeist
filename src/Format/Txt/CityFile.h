#pragma once

// Project includes
#include "../Dat/Item.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Txt
        {
            /**
             * @brief City entrance information.
             */
            struct CityEntrance
            {
                /**
                 * Start state of entrance (visible or not)
                 */
                bool startState;
                /**
                 * X coordinate on town map
                 */
                int townMapX;
                /**
                 * Y coordinate on town map
                 */
                int townMapY;
                /**
                 * Name of associated map
                 */
                std::string mapName;
                /**
                 * Starting elevation
                 */
                int elevation;
                /**
                 * Starting tile number
                 */
                int tileNum;
                /**
                 * Starting orientation
                 */
                int orientation;
            };

            /**
             * @brief City information.
             */
            struct City
            {
                enum class Size
                {
                    Small = 1, Medium, Large
                };

                std::string name;
                int worldX = 0;
                int worldY = 0;
                bool startState;
                Size size;

                int townMapArtIdx;
                int townMapLabelArtIdx;

                std::vector<CityEntrance> entrances;
            };

            /**
             * @brief CITY.TXT
             */
            class CityFile : public Dat::Item
            {
                public:
                    CityFile(Dat::Stream&& stream);

                    const std::vector<City>& cities() const;

                protected:
                    std::vector<City> _cities;


                    void _parseText(std::istream& istr);

                    City::Size _sizeByName(std::string name) const;
            };
        }
    }
}
