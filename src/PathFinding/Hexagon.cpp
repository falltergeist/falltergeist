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
    int dx = hexagon->cubeX() - cubeX();
    int dy = hexagon->cubeY() - cubeY();

    switch(dx)
    {
        case 0: // 0 || 3
        {
            return dy == 1 ? 0 : 3;
        }
        case 1: // 1 || 2
        {
            return dy == 0 ? 1 : 2;
        }
        case -1: // 4 || 5
        {
            return dy == 0 ? 4 : 5;
        }
    }
    return 0;
}

}
