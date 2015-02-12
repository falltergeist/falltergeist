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
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Tile.h"

// Third party includes

namespace Falltergeist
{

Tile::Tile(unsigned int number, int x, int y)
{
    _number = number;
    _x = x;
    _y = y;
}

unsigned int Tile::number()
{
    return _number;
}

int Tile::x()
{
    return _x;
}

int Tile::y()
{
    return _y;
}

unsigned int Tile::index()
{
    return _index;
}

void Tile::setIndex(unsigned int value)
{
    _index = value;
}

}
