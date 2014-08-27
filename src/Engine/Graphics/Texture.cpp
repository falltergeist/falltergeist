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
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/Game.h"
#include "../../Engine/Graphics/Renderer.h"

// Third party includes

namespace Falltergeist
{

Texture::Texture(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    _data = new unsigned int[width*height](); // RGBA data for each pixel
}

Texture::~Texture()
{
    auto game = &Game::getInstance();
    //game->renderer()->unregisterTexture(this);
    delete [] _data;
}

unsigned int Texture::id()
{
    return _id;
}

void Texture::setId(unsigned int value)
{
    _id = value;
}

unsigned int Texture::width()
{
    return _width;
}

unsigned int Texture::height()
{
    return _height;
}

unsigned int* Texture::data()
{
    return _data;
}

unsigned int Texture::pixel(unsigned int x, unsigned int y)
{
    if (x >= _width || y >= _height) return 0;
    unsigned int index = (y*_width) + x;
    return _data[index];
}

void Texture::setPixel(unsigned int x, unsigned int y, unsigned int color)
{
    if (x >= _width || y >= _height) return;
    unsigned int index = (y*_width) + x;
    _data[index] = color;
}

void Texture::loadFromRGBA(unsigned int* data)
{
    for (unsigned int i = 0; i != _width*_height; ++i) _data[i] = data[i];
}

}
