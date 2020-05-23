#include "../Map/Elevation.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            Elevation::Elevation()
            {
            }

            std::vector<std::shared_ptr<Object>>& Elevation::objects()
            {
                return _objects;
            }

            const std::vector<std::shared_ptr<Object>>& Elevation::objects() const
            {
                return _objects;
            }

            std::vector<uint16_t>& Elevation::floorTiles()
            {
                return _floorTiles;
            }

            const std::vector<uint16_t>& Elevation::floorTiles() const
            {
                return _floorTiles;
            }

            std::vector<uint16_t>& Elevation::roofTiles()
            {
                return _roofTiles;
            }

            const std::vector<uint16_t>& Elevation::roofTiles() const
            {
                return _roofTiles;
            }
        }
    }
}
