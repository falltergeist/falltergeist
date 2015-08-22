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

// C++ standard includes
#include <functional>
#include <queue>
#include <cstdlib>

// Falltergeist includes
#include "../PathFinding/Hexagon.h"
#include "../PathFinding/HexagonGrid.h"

// Third party includes

namespace Falltergeist
{

struct HeuristicComparison : public std::binary_function<Hexagon*, Hexagon*, bool>
{
    bool operator()(Hexagon* lh, Hexagon* rh) const
    {
        return lh->heuristic() > rh->heuristic();
    }
};


HexagonGrid::HexagonGrid()
{
    // Creating 200x200 hexagonal map
    unsigned int index = 0;
    for (unsigned int q = 0; q != 200; ++q)
    {
        for (unsigned int p = 0; p != 200; ++p, ++index)
        {
            auto hexagon = new Hexagon(index);
            int x = 48*100 + 16*(q+1) - 24*p;
            int y = (q+1)*12 + 6*p + 12;
            if (p&1)
            {
                x -= 8;
                y -= 6;
            }

            hexagon->setCubeX(q - (p + (p&1))/2);
            hexagon->setCubeZ(p);
            hexagon->setCubeY(-hexagon->cubeX() - hexagon->cubeZ());

            hexagon->setPosition({x, y});
            _hexagons.push_back(hexagon);
        }
    }

    // Creating links between hexagons
    for (index = 0; index != 200*200; ++index)
    {
        auto hexagon = _hexagons.at(index);

        unsigned int q = index/200; // hexagonal y
        unsigned int p = index%200; // hexagonal x

        unsigned index1 = (q + 1)*200 + p;
        unsigned index4 = (q-1)*200 + p;
        unsigned int index2, index3, index5, index6;
        if (index&1)
        {
            index2 = q*200 + p-1;
            index3 = (q-1)*200 + p-1;
            index5 = (q-1)*200 + p+1;
            index6 = q*200 + p+1;
        }
        else
        {
            index2 = (q+1)*200 + p-1;
            index3 = q*200 + p-1;
            index5 = q*200 + p+1;
            index6 = (q+1)*200 + p+1;
        }

        if (index1 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index1));
        if (index2 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index2));
        if (index3 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index3));
        if (index4 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index4));
        if (index5 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index5));
        if (index6 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index6));
    }
}

HexagonGrid::~HexagonGrid()
{
    while (!_hexagons.empty())
    {
        delete _hexagons.back();
        _hexagons.pop_back();
    }
}

Hexagon* HexagonGrid::at(unsigned int index)
{
    return _hexagons.at(index);
}

Hexagon* HexagonGrid::hexagonAt(const Point& pos)
{
    for (auto hexagon : _hexagons)
    {
        auto hexPos = hexagon->position();
        if (pos.x() >= hexPos.x() - 16
            && pos.x() < hexPos.x() + 16
            && pos.y() >= hexPos.y() - 8
            && pos.y() < hexPos.y() + 4)
        {
            return hexagon;
        }
    }
    return nullptr;
}

std::vector<Hexagon*>* HexagonGrid::hexagons()
{
    return &_hexagons;
}

std::vector<Hexagon*> HexagonGrid::findPath(Hexagon* from, Hexagon* to)
{
    Hexagon* current = 0;
    std::vector<Hexagon*> result;
    std::priority_queue<Hexagon*, std::vector<Hexagon*>, HeuristicComparison> unvisited;
    unsigned int cameFrom[200*200] = {};
    unsigned int costSoFar[200*200] = {};

    // if we can't go to the location
    // @todo remove when path will have lenght restriction
    if (!to->canWalkThru()) return result;

    unvisited.push(from);

    cameFrom[from->number()] = 0;
    costSoFar[from->number()] = 0;


    while (!unvisited.empty())
    {
        current = unvisited.top(); unvisited.pop();
        if (current == to) break;
        // search limit
        if (costSoFar[current->number()] >= 100) break;

        for (Hexagon* neighbor : *current->neighbors())
        {
            if (!neighbor->canWalkThru()) continue;

            unsigned int newCost = costSoFar[current->number()] + 1;
            if (!costSoFar[neighbor->number()] || newCost < costSoFar[neighbor->number()])
            {
                costSoFar[neighbor->number()] = newCost;
                neighbor->setHeuristic(distance(neighbor, to) + newCost);
                unvisited.push(neighbor);
                cameFrom[neighbor->number()] = current->number();
            }
        }
    }

    // found nothing
    if (current != to) return result;


    while (current->number() != from->number())
    {
        result.push_back(current);
        current = _hexagons.at(cameFrom[current->number()]);
    }

    return result;
}

unsigned int HexagonGrid::distance(Hexagon* from, Hexagon* to)
{
    return (std::abs(from->cubeX() - to->cubeX()) + std::abs(from->cubeY() - to->cubeY()) + std::abs(from->cubeZ() - to->cubeZ())) / 2;
}

Hexagon* HexagonGrid::hexInDirection(Hexagon* from, unsigned short rotation, unsigned int distance)
{
    if (distance == 0 || rotation > 5)
    {
        return from;
    }

    int startX = from->cubeX();
    int startY = from->cubeY();
    int startZ = from->cubeZ();

    switch (rotation)
    {
        case 0:
            startY+=distance;
            startZ-=distance;
            break;
        case 1:
            startZ-=distance;
            startX+=distance;
            break;
        case 2:
            startX+=distance;
            startY-=distance;
            break;
        case 3:
            startY-=distance;
            startZ+=distance;
            break;
        case 4:
            startZ+=distance;
            startX-=distance;
            break;
        case 5:
            startX-=distance;
            startY+=distance;
            break;

    }
    int p = startZ;
    int q = startX + (p + (p&1))/2;
    int index = 200*q + p;
    if (index < 0 || index >= 200*200)
    {
        return from;
    }
    return at(index);

}

std::vector<Hexagon*> HexagonGrid::ring(Hexagon* from, unsigned int radius)
{
    std::vector<Hexagon*> result;
    Hexagon* current = nullptr;
    unsigned int dir = 0;
    if (radius == 0)
    {
        result.push_back(from);
        return result;
    }
    current = hexInDirection(from, dir, radius);
    dir = 2;
    for (unsigned int d = 0; d < 6; d++)
    {
        for (unsigned int i = 0; i < radius; i++)
        {
            result.push_back(current);
            current = hexInDirection(current,dir,1);
        }
        dir++;
        if (dir > 5)
        {
            dir = 0;
        }
    }
    return result;
}

}
