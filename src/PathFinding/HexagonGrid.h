#pragma once

#include <array>
#include <vector>
#include "../Base/Iterators.h"
#include "../Graphics/Point.h"

#define GRID_WIDTH 200
#define GRID_HEIGHT 200

namespace Falltergeist
{
    class Hexagon;

    class HexagonGrid
    {
        using HexagonVector = std::vector<std::shared_ptr<Hexagon>>;

        public:
            HexagonGrid();
            ~HexagonGrid();
            Base::vector_ptr_decorator<Hexagon> hexagons();

            unsigned int distance(Hexagon *from, Hexagon *to);
            std::shared_ptr<Hexagon> hexagonAt(const Graphics::Point& pos);
            const std::shared_ptr<Falltergeist::Hexagon> &at(size_t index);
            HexagonVector findPath(Hexagon* from, Hexagon* to);
            std::shared_ptr<Hexagon> hexInDirection(const std::shared_ptr<Hexagon> &from, unsigned short rotation, unsigned int distance);
            HexagonVector ring(const std::shared_ptr<Hexagon> &from, unsigned int radius);
            void initLight(const std::shared_ptr<Hexagon> &hex, bool add = true);

        protected:
            HexagonVector _hexagons; // The 200x200 grid
    };
}
