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

#ifndef FALLTERGEIST_HEXAGON_H
#define FALLTERGEIST_HEXAGON_H

// C++ standard includes
#include <vector>
#include <list>

// Falltergeist includes
#include "../Game/Object.h"
#include "../Graphics/Point.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class Object;
}

using Graphics::Point;

class Hexagon
{
public:
    Hexagon();
    Hexagon(unsigned int number);

    const Point& position() const;
    void setPosition(const Point& pos);

    unsigned int number();
    void setNumber(unsigned int number);

    std::vector<Hexagon*>* neighbors();

    std::list<Game::Object*>* objects();

    int cubeX();
    void setCubeX(int value);

    int cubeY();
    void setCubeY(int value);

    int cubeZ();
    void setCubeZ(int value);

    unsigned int heuristic();
    void setHeuristic(unsigned int value);

    bool canWalkThru();

    void setInRender(bool value);
    bool inRender();

    Game::Orientation orientationTo(Hexagon *hexagon);

    unsigned int addLight(unsigned int light);
    unsigned int subLight(unsigned int light);
    unsigned int setLight(unsigned int light);
    unsigned int light();

protected:
    std::vector<Hexagon*> _neighbors;
    std::list<Game::Object*> _objects;
    unsigned int _number = 0; // position in hexagonal grid

    Point _position;

    int _cubeX = 0;
    int _cubeY = 0;
    int _cubeZ = 0;

    unsigned int _heuristic = 0;

    bool _inRender = false;

    unsigned int _light = 655;
};

}
#endif // FALLTERGEIST_HEXAGON_H
