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
#include "../Engine/Hexagon.h"
#include "../Engine/Game.h"

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

bool Hexagon::checked()
{
    return _checked;
}

void Hexagon::setChecked(bool value)
{
    _checked = value;
}

Hexagon* Hexagon::cameFrom()
{
    return _cameFrom;
}

void Hexagon::setCameFrom(Hexagon* cameFrom)
{
    _cameFrom = cameFrom;
}

std::vector<Hexagon*>* Hexagon::neighbors()
{
    return &_neighbors;
}

std::list<std::shared_ptr<GameObject>>* Hexagon::objects()
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

}
