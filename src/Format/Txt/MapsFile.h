#pragma once

#include <map>
#include <vector>
#include "../Dat/Item.h"

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
            struct MapStartPoint
            {
                int elevation = 0;
                int tileNum = 0;
            };

            /**
             * @brief Map information.
             */
            struct Map
            {
                static const char NUM_ELEVATIONS = 3;

                std::string name;
                std::string lookupName;
                std::string music;
                /**
                 * Keys are sfx names, value - probability in %. Probabilities *should* sum up to 100.
                 */
                std::map<std::string, unsigned char> ambientSfx;
                bool deadBodiesAge;
                /**
                 * Flag for each elevation.
                 */
                bool canRestHere[NUM_ELEVATIONS] = {true, true, true};
                bool saved;

                std::vector<MapStartPoint> randomStartPoints;
            };

            /**
             * @brief CITY.TXT
             */
            class MapsFile : public Dat::Item
            {
                public:
                    MapsFile(Dat::Stream&& stream);

                    const std::vector<Map>& maps() const;

                protected:
                    std::vector<Map> _maps;

                    void _parseText(std::istream& istr);
            };
        }
    }
}
