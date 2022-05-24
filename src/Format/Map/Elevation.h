#pragma once

// Project includes
#include "../Map/Object.h"

// Third-party includes

// stdlib
#include <memory>
#include <vector>

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
