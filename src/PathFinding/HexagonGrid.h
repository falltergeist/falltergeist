#pragma once

// Project includes
#include "../Base/Iterators.h"
#include "../Graphics/Point.h"

// Third-party includes

// stdlib
#include <array>
#include <vector>

namespace Falltergeist
{
    class Hexagon;

    class HexagonGrid
    {
        using HexagonVector = std::vector<std::unique_ptr<Hexagon>>;

        public:
            static constexpr unsigned GRID_WIDTH = 200;
            static constexpr unsigned GRID_HEIGHT = 200;

            HexagonGrid();
            ~HexagonGrid();
            Base::vector_ptr_decorator<Hexagon> hexagons();

            unsigned int distance(Hexagon* from, Hexagon* to);
            Hexagon* hexagonAt(const Graphics::Point& pos);
            Hexagon* at(size_t index);
            std::vector<Hexagon*> findPath(Hexagon* from, Hexagon* to);
            Hexagon* hexInDirection(Hexagon* from, unsigned short rotation, unsigned int distance);
            std::vector<Hexagon*> ring(Hexagon* from, unsigned int radius);
            void initLight(Hexagon* hex, bool add = true);

        protected:
            HexagonVector _hexagons; // The 200x200 grid
    };
}
