/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_HEXAGONGRID_H
#define FALLTERGEIST_HEXAGONGRID_H

// C++ standard includes
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Hexagon;

class HexagonGrid
{
protected:
    std::vector<Hexagon*> _hexagons;
public:
    HexagonGrid();
    ~HexagonGrid();
    std::vector<Hexagon*>* hexagons();
    unsigned int distance(Hexagon* from, Hexagon* to);
    Hexagon* hexagonAt(unsigned int x, unsigned int y);
    Hexagon* at(unsigned int index);
    std::vector<Hexagon*> findPath(Hexagon* from, Hexagon* to);
    Hexagon* hexInDirection(Hexagon* from, unsigned short rotation, unsigned int distance);
    std::vector<Hexagon*> ring(Hexagon* from, unsigned int radius);
};

}
#endif // FALLTERGEIST_HEXAGONGRID_H
