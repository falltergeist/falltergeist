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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Graphics/Texture.h"
#include "../Engine/Tile.h"

// Third party includes

namespace Falltergeist
{

Tile::Tile(int x, int y)
{
    _x = x;
    _y = y;
}

int Tile::x()
{
    return _x;
}

void Tile::setX(int value)
{
    _x = value;
}

int Tile::offsetX()
{
    return _offsetX;
}

void Tile::setOffsetX(int value)
{
    _offsetX = value;
}

int Tile::y()
{
    return _y;
}

void Tile::setY(int value)
{
    _y = value;
}

int Tile::offsetY()
{
    return _offsetY;
}

void Tile::setOffsetY(int value)
{
    _offsetY = value;
}

std::shared_ptr<Texture> Tile::texture()
{
    return _texture;
}

void Tile::setTexture(std::shared_ptr<Texture> texture)
{
    _texture = texture;
}

void Tile::render()
{
    Game::getInstance()->renderer()->drawTexture(_texture, _x + _offsetX, _y + _offsetY);
}

}
