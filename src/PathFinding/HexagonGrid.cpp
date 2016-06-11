/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <array>
#include <cstdlib>
#include <functional>
#include <queue>
#include <memory>

// Falltergeist includes
#include "../Game/WallObject.h"
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
            _hexagons.emplace_back(std::make_unique<Hexagon>(index));
            auto& hexagon = _hexagons.back();
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
        }
    }

    // Creating links between hexagons
    for (index = 0; index != 200*200; ++index)
    {
        auto hexagon = _hexagons.at(index).get();

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

        if (index1 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index1).get());
        if (index2 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index2).get());
        if (index3 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index3).get());
        if (index4 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index4).get());
        if (index5 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index5).get());
        if (index6 < _hexagons.size()) hexagon->neighbors()->push_back(_hexagons.at(index6).get());
    }
}

HexagonGrid::~HexagonGrid()
{
}

Hexagon* HexagonGrid::at(size_t index)
{
    return _hexagons.at(index).get();
}

Hexagon* HexagonGrid::hexagonAt(const Point& pos)
{
    for (auto& hexagon : _hexagons)
    {
        auto hexPos = hexagon->position();
        if (pos.x() >= hexPos.x() - 16
            && pos.x() < hexPos.x() + 16
            && pos.y() >= hexPos.y() - 8
            && pos.y() < hexPos.y() + 4)
        {
            return hexagon.get();
        }
    }
    return nullptr;
}

Base::vector_ptr_decorator<Hexagon> HexagonGrid::hexagons()
{
    return Base::vector_ptr_decorator<Hexagon>(_hexagons);
}

std::vector<Hexagon*> HexagonGrid::findPath(Hexagon* from, Hexagon* to)
{
    Hexagon* current = nullptr;
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
        current = _hexagons.at(cameFrom[current->number()]).get();
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
        return nullptr;
    }
    return at(index);

}

std::vector<Hexagon*> HexagonGrid::ring(Hexagon* from, unsigned int radius)
{
    std::vector<Hexagon*> result;

    if (radius == 0)
    {
        result.push_back(from);
        return result;
    }

    unsigned int dir = 0;
    Hexagon* current = hexInDirection(from, dir, radius);
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

void HexagonGrid::initLight(Hexagon *hex, bool add)
{


    auto objectsAtHex = hex->objects();
    for (auto it = objectsAtHex->begin(); it != objectsAtHex->end(); ++it)
    {
        auto object = *it;
        if (object->lightIntensity()>0 && object->lightRadius()>0)
        {
            // 36 hexes per direction
            std::array<bool, 36*6> blocked;
            blocked.fill(false);

            auto prevTwo = [&blocked](int idx, int radius, int dir) -> bool
            {
                idx = idx-(radius-1)*6-dir;
                return blocked[idx-1] && blocked[idx];
            };

            auto isBlocked = [&blocked](int coneIdx, int radius, int dir) -> bool
            {
                dir = dir % 6;
                int base = 0;
                int r = radius;
                while (r>0)
                {
                    base+=(r-1)*6;
                    r--;
                }


                return blocked[base+coneIdx+radius*dir];
            };

            auto index = [](int coneIdx, int radius, int dir) -> int
            {
                dir = dir % 6;
                int base = 0;
                int r = radius;
                while (r>0)
                {
                    base+=(r-1)*6;
                    r--;
                }


                return base+coneIdx+radius*dir;
            };

            int light = object->lightIntensity();
            if (add)
            {
                hex->addLight(light);
            }
            else
            {
                hex->subLight(light);
            }
            int perRadius = (light - 655) / (object->lightRadius()+1);

            int blockerIndex = 0;

            for (unsigned int radius = 1; radius<= object->lightRadius();radius++)
            {
                light-=perRadius;
                int ringIndex=0;
                for (auto ringhex : ring(hex,radius))
                {
                    if (!ringhex) //invalid hex
                    {
                        ringIndex++;
                        blockerIndex++;
                        continue;
                    }
                    int dir = ringIndex / radius;

                    int coneIdx = ringIndex % radius;

                    bool block = false;
                    switch (radius)
                    {
                        case 1:
                            block = false;
                            break;
                        case 2:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                            }
                            break;
                        case 3:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                                case 2:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                            }
                            break;
                        case 4:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                                case 2:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || isBlocked(1, 2, dir);
                                    break;
                                case 3:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || prevTwo(index(2,3,dir),radius-1,dir) ;
                                    break;
                            }
                            break;
                        case 5:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                                case 2:

                                    block = (isBlocked(1, 3, dir) && (isBlocked(2,3,dir) || isBlocked(1, 4, dir)))
                                            || (isBlocked(2,4,dir) && (isBlocked(1, 4, dir) || isBlocked(1, 3, dir)))
                                            || ((isBlocked(1, 4, dir) || isBlocked(1, 3, dir)) & isBlocked(1,2,dir));
                                    break;
                                case 3:
                                    block = ((isBlocked(3, 4, dir) || isBlocked(2, 3, dir)) && isBlocked(2, 4, dir))
                                            || (isBlocked(2, 3, dir) && (isBlocked(3, 4, dir) || isBlocked(1, 3, dir)))
                                            || ((isBlocked(3, 4, dir) || isBlocked(2, 3, dir) || isBlocked(0, 2, dir + 1)) && isBlocked(1, 2, dir));
                                    break;
                                case 4:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || prevTwo(index(3,4,dir),radius-1,dir)
                                            || prevTwo(index(2,3,dir),radius-2,dir);
                                    break;
                            }
                            break;
                        case 6:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                                case 2:
                                    block = ((isBlocked(1,5, dir) || isBlocked(1,4,dir) || isBlocked(1,3,dir) || isBlocked(0,1,dir)) && isBlocked(2,5,dir))
                                            || isBlocked(1,3,dir)
                                            || (isBlocked(2,4,dir) && isBlocked(1,4,dir));
                                    break;
                                case 3:
                                    block =  prevTwo(blockerIndex, radius, dir)
                                            || prevTwo(index(2,4,dir), radius-2, dir)
                                            || isBlocked(1,2,dir)
                                            || isBlocked(2,4,dir);
                                    break;
                                case 4:
                                    block = (prevTwo(index(3,5,dir), radius-1, dir)
                                            || isBlocked(1,2,dir))
                                            || isBlocked(2,3,dir)
                                            || prevTwo(index(2,3,dir), radius-3, dir)
                                            || ((isBlocked(4,5,dir) || isBlocked(3,4,dir) || isBlocked(2,3,dir) || isBlocked(0,1, dir+1))
                                                && isBlocked(3,5,dir));
                                    break;
                                case 5:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || prevTwo(index(4,5,dir),radius-1,dir)
                                            || prevTwo(index(3,4,dir),radius-2,dir)
                                            || prevTwo(index(2,3,dir),radius-3,dir);
                                    break;
                            }
                            break;
                        case 7:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                                case 2:
                                    block = prevTwo(blockerIndex,radius,dir)
                                                     || isBlocked(1,4,dir)
                                                     || isBlocked(1,3,dir)
                                                     || ((isBlocked(0, radius-1, dir) || isBlocked(2,5,dir)) && isBlocked(1,5,dir));

                                    break;
                                case 3:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || (isBlocked(2,5,dir) && (isBlocked(3,6,dir) || isBlocked(3,5,dir) || isBlocked(2,3,dir)))
                                            || isBlocked(1,2,dir)
                                            || (isBlocked(1,3,dir) && (isBlocked(3,6,dir) || isBlocked(2,4,dir) || isBlocked(2,3,dir)))
                                            || ((isBlocked(2,6,dir) || isBlocked(2,5,dir) || isBlocked(1,4,dir) || isBlocked(1,3,dir) || isBlocked(0,1,dir)) && isBlocked(2,4,dir));

                                    break;
                                case 4:
                                    block = prevTwo(blockerIndex, radius, dir)
                                            || (isBlocked(3,5,dir) && (isBlocked(3,6,dir) || isBlocked(2,5,dir) || isBlocked(1,3,dir)))
                                            || (isBlocked(2,4,dir) && (isBlocked(4,6,dir) || isBlocked(3,5,dir) || isBlocked(3,4,dir) || isBlocked(0,1,dir+1)))
                                            || isBlocked(1,2,dir)
                                            || (isBlocked(2,3,dir) && (isBlocked(3,6,dir) || isBlocked(2,4,dir) || isBlocked(1,3,dir)));

                                    break;
                                case 5:
                                    block = prevTwo(blockerIndex,radius, dir)
                                            || (isBlocked(4,5,dir) && (isBlocked(4,6,dir) || isBlocked(3,5,dir) || isBlocked(1,2,dir)))
                                            || isBlocked(2,3,dir)
                                            || (isBlocked(0,2,dir+1) && isBlocked(1,2,dir))
                                            || isBlocked(3,4,dir);

                                    break;
                                case 6:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || prevTwo(index(5,6,dir),radius-1,dir)
                                            || prevTwo(index(4,5,dir),radius-2,dir)
                                            || prevTwo(index(3,4,dir),radius-3,dir)
                                            || prevTwo(index(2,3,dir),radius-4,dir);
                                    break;
                            }
                            break;
                        case 8:
                            switch (coneIdx)
                            {
                                case 0:
                                    block = isBlocked(0, radius-1, dir);
                                    break;
                                case 1:
                                    block = prevTwo(blockerIndex,radius,dir);
                                    break;
                                case 2:
                                    block = ((isBlocked(2,7,dir) || isBlocked(2,6,dir) || isBlocked(2,5,dir) || isBlocked(2,4,dir)) && isBlocked(1,5,dir))
                                            || ((isBlocked(1,6,dir) || isBlocked(1,5,dir) || isBlocked(0,3,dir)) && isBlocked(1,2,dir))
                                            || (isBlocked(1,3,dir) && (isBlocked(1,6,dir) || isBlocked(1,5,dir) || isBlocked(0,3,dir)))
                                            || isBlocked(1,4,dir);
                                    break;
                                case 3:
                                    block = (isBlocked(3,7,dir) && (isBlocked(2,7,dir) || isBlocked(0,1,dir)))
                                            || (isBlocked(2,6,dir) && (isBlocked(3,7,dir) || isBlocked(3,6,dir) || isBlocked(2,4,dir) || isBlocked(1,2,dir)))
                                            || isBlocked(2,5,dir)
                                            || (isBlocked(1,4,dir) && (isBlocked(3,7,dir) || isBlocked(2,4,dir) || isBlocked(1,2,dir) || isBlocked(2,5,dir)))
                                            || (isBlocked(0,2,dir) && isBlocked(1,2,dir))
                                            || ((isBlocked(3,7,dir) || isBlocked(3,6,dir) || isBlocked(2,4,dir) || isBlocked(2,3,dir) || isBlocked(1,2,dir)) && isBlocked(1,3,dir));

                                    break;
                                case 4:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || prevTwo(index(3,6,dir),radius-2,dir)
                                            || prevTwo(index(2,4,dir),radius-4,dir)
                                            || isBlocked(3,6,dir)
                                            || isBlocked(2,4,dir)
                                            || isBlocked(1,2,dir);
                                    break;
                                case 5:
                                    block = (isBlocked(4,7,dir) && (isBlocked(5,7,dir) || isBlocked(0,1,dir)))
                                            || (isBlocked(4,6,dir) && (isBlocked(4,7,dir) || isBlocked(3,6,dir) || isBlocked(2,4,dir) || isBlocked(1,2,dir)))
                                            || isBlocked(3,5,dir)
                                            || (isBlocked(0,2,dir+1) && isBlocked(1,2,dir))
                                            || ((isBlocked(4,7,dir) || isBlocked(3,6,dir) || isBlocked(2,4,dir) || isBlocked(1,3,dir) || isBlocked(1,2,dir)) && isBlocked(2,3,dir))
                                            || (isBlocked(3,4,dir) && (isBlocked(2,4,dir) || isBlocked(1,2,dir) || isBlocked(4,7,dir)));
                                    break;
                                case 6:
                                    block = ((isBlocked(5,7,dir) || isBlocked(4,6,dir) || isBlocked(3,5,dir) || isBlocked(2,4,dir)) && isBlocked(4,5,dir))
                                            || isBlocked(3,4,dir)
                                            || (isBlocked(2,3,dir) && (isBlocked(5,6,dir) || isBlocked(4,5,dir) || isBlocked(0,3,dir+1)))
                                            || ((isBlocked(5,6,dir) || isBlocked(4,5,dir) || isBlocked(0,3,dir+1)) && isBlocked(1,2,dir));

                                    break;
                                case 7:
                                    block = prevTwo(blockerIndex,radius,dir)
                                            || prevTwo(index(6,7,dir),radius-1,dir)
                                            || prevTwo(index(5,6,dir),radius-2,dir)
                                            || prevTwo(index(4,5,dir),radius-3,dir)
                                            || prevTwo(index(3,4,dir),radius-4,dir)
                                            || prevTwo(index(2,3,dir),radius-5,dir);
                                    break;
                            }
                            break;
                        default:
                            break;

                    }

                    if (!block)
                    {
                        // find objs/walls
                        bool lightHex = true;
                        for (auto it2 = ringhex->objects()->begin(); it2 != ringhex->objects()->end(); ++it2)
                        {
                            auto curObject = *it2;
                            // dead objects block nothing
                            //if (curObject->dead()) continue;
                            // flat objects block nothing
                            if (curObject->flat()) continue;
                            if (curObject->type()==Game::Object::Type::DUDE) continue;

                            if (!curObject->canLightThru())
                            {
                                // if wall -> check light orientation
                                if (auto wall = dynamic_cast<Game::WallObject*>(curObject))
                                {
                                    if (wall->lightOrientation() == Game::Orientation::EW || wall->lightOrientation() == Game::Orientation::EC)
                                    {
                                        if ( (dir != 4) && (dir != 5) && (dir>0 || coneIdx > 0) && (dir != 3 || ((coneIdx>=0 && coneIdx<=1) || (radius==3 && coneIdx==2) )))
                                        {
                                            lightHex = false;
                                        }
                                    }
                                    else if (wall->lightOrientation() == Game::Orientation::NC)
                                    {
                                        if( dir != 0 && dir != 5)
                                        {
                                            lightHex = false;
                                        }
                                    }
                                    else if (wall->lightOrientation() == Game::Orientation::SC)
                                    {
                                        if( (dir>0) && dir != 1 && dir != 4 && dir != 5 && (dir != 3 || ((coneIdx>=0 && coneIdx<=1) || (radius==3 && coneIdx==2) )))
                                        {
                                            lightHex = false;
                                        }
                                    }
                                    else if (dir != 0 && dir != 1 && ( dir != 5 || coneIdx==0 ))
                                    {
                                        lightHex = false;
                                    }
                                }
                                else
                                {
                                    if (dir>=1 && dir <=3 )
                                    {
                                        lightHex=false;
                                    }
                                }

                                block = true;

                                break;
                            }

                        }
                        if (lightHex)
                        {
                            if (add) {
                                ringhex->addLight(light);
                            }
                            else {
                                ringhex->subLight(light);
                            }
                        }
                    }

                    blocked[blockerIndex] = block;
                    ringIndex++;
                    blockerIndex++;
                }

            }
        }
    }

}
}
