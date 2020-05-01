#pragma once

#include <memory>
#include <vector>
#include "../Map/Object.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            class Elevation
            {
                public:
                    Elevation();
                    std::vector<std::unique_ptr<Object>>& objects();
                    const std::vector<std::unique_ptr<Object>>& objects() const;
                    std::vector<uint16_t>& floorTiles();
                    const std::vector<uint16_t>& floorTiles() const;
                    std::vector<uint16_t>& roofTiles();
                    const std::vector<uint16_t>& roofTiles() const;

                protected:
                    std::vector<uint16_t> _floorTiles;
                    std::vector<uint16_t> _roofTiles;
                    std::vector<std::unique_ptr<Object>> _objects;
            };
        }
    }
}
