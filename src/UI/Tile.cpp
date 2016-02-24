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

// Related headers
#include "../UI/Tile.h"

// C++ standard includes

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

Tile::Tile(unsigned int number, const Point& pos)
{
    _number = number;
    _position = pos;
}

unsigned int Tile::number() const
{
    return _number;
}

Point Tile::position() const
{
    return _position;
}

unsigned int Tile::index() const
{
    return _index;
}

void Tile::setIndex(unsigned int value)
{
    _index = value;
}

void Tile::enable()
{
    _enabled = true;
}

void Tile::disable()
{
    _enabled = false;
}

bool Tile::enabled()
{
    return _enabled;
}
}
}
