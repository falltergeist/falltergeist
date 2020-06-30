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
            const std::shared_ptr<Falltergeist::Hexagon> &at(size_t index) const;
            HexagonVector findPath(Hexagon* from, Hexagon* to);
            Hexagon *hexInDirection(Falltergeist::Hexagon *from, unsigned short rotation, unsigned int distance) const;
            std::vector<Hexagon*> ring(Hexagon *from, unsigned int radius) const;
            void initLight(Falltergeist::Hexagon *hex, bool add = true) const;

        protected:
            HexagonVector _hexagons; // The 200x200 grid
    };
}
