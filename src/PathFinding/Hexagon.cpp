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
#include <cmath>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../Game/Object.h"
#include "../Game/DoorSceneryObject.h"

// Third party includes

namespace Falltergeist
{

Hexagon::Hexagon()
{
}

Hexagon::Hexagon(unsigned int number)
{
    setNumber(number);
}

unsigned int Hexagon::number()
{
    return _number;
}

void Hexagon::setNumber(unsigned int number)
{
    _number = number;
}

std::vector<Hexagon*>* Hexagon::neighbors()
{
    return &_neighbors;
}

std::list<Game::GameObject*>* Hexagon::objects()
{
    return &_objects;
}

int Hexagon::x()
{
    return _x;
}

void Hexagon::setX(int value)
{
    _x = value;
}

int Hexagon::y()
{
    return _y;
}

void Hexagon::setY(int value)
{
    _y = value;
}

int Hexagon::cubeX()
{
    return _cubeX;
}

void Hexagon::setCubeX(int value)
{
    _cubeX = value;
}

int Hexagon::cubeY()
{
    return _cubeY;
}

void Hexagon::setCubeY(int value)
{
    _cubeY = value;
}

int Hexagon::cubeZ()
{
    return _cubeZ;
}

void Hexagon::setCubeZ(int value)
{
    _cubeZ = value;
}

unsigned int Hexagon::heuristic()
{
    return _heuristic;
}

void Hexagon::setHeuristic(unsigned int value)
{
    _heuristic = value;
}

bool Hexagon::canWalkThru()
{
    bool canWalkThru = true;
    for (auto object : _objects)
    {
        if (auto door = dynamic_cast<Game::GameDoorSceneryObject*>(object))
        {
            return door->canWalkThru();
        }
        if (!object->canWalkThru()) canWalkThru = false;
    }
    return canWalkThru;
}

bool Hexagon::inRender()
{
    return _inRender;
}

void Hexagon::setInRender(bool value)
{
    _inRender = value;
}

unsigned int Hexagon::orientationTo(Hexagon* hexagon)
{

    int x1 = x();
    int y1 = y();
    int x2 = hexagon->x();
    int y2 = hexagon->y();
    int dx = x2 - x1;
    int dy = y2 - y1;

    unsigned int result = 0;

    if (dx)
    {
        // triginometry magick.
        // basically, we try to find angle to second hex in circle, where first hex is center
        // and then find out to which of 60º slices it belongs

        double degree = atan2((double)-dy, (double)dx) * 180.0 * 0.3183098862851122; //  180 * 1/PI

        result = (360 - ((signed int)degree + 180) - 90 + ((char)-(360 - ((signed int)degree + 180) - 90 < 0) & 360)) / 60;
        if ( result > 5 )
        {
            result = 5;
        }
    }
    else if ( dy < 0 )
    {
        result = 0;
    }
    else
    {
        result = 2;
    }

    return result;
}

}
