/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// Falltergeist includes
#include "../../Engine/Game.h"
#include "../../Engine/PathFinding/Hexagon.h"
#include "../../Game/GameObject.h"

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

std::list<GameObject*>* Hexagon::objects()
{
    return &_objects;
}

unsigned int Hexagon::x()
{
    return _x;
}

void Hexagon::setX(unsigned int value)
{
    _x = value;
}

unsigned int Hexagon::y()
{
    return _y;
}

void Hexagon::setY(unsigned int value)
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
    for (auto object : _objects)
    {
        if (!object->canWalkThru()) return false;
    }
    return true;
}

}
