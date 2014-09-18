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
    _unregister();
    delete [] _data;
}

void Texture::_unregister()
{
    if (!id()) return;
    auto game = Game::getInstance();
    game->renderer()->unregisterTexture(this);
    _id = 0;
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
    _unregister();
    unsigned int index = (y*_width) + x;
    _data[index] = color;    
}

void Texture::loadFromRGBA(unsigned int* data)
{
    _unregister();
    for (unsigned int i = 0; i != _width*_height; ++i) _data[i] = data[i];    
}

void Texture::copyTo(std::shared_ptr<Texture> destination, unsigned int destinationX, unsigned int destinationY, unsigned int sourceX, unsigned int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    if (sourceWidth == 0) sourceWidth = width();
    if (sourceHeight == 0) sourceHeight = height();

    for (unsigned int y = 0; y != sourceHeight; y++)
    {
        for(unsigned int x = 0; x != sourceWidth; x++)
        {
            destination->setPixel(destinationX + x, destinationY + y, pixel(sourceX + x, sourceY + y));
        }
    }
}

void Texture::blitTo(std::shared_ptr<Texture> destination, unsigned int destinationX, unsigned int destinationY, unsigned int sourceX, unsigned int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    if (sourceWidth == 0) sourceWidth = width();
    if (sourceHeight == 0) sourceHeight = height();

    for (unsigned int y = 0; y != sourceHeight; y++)
    {
        for(unsigned int x = 0; x != sourceWidth; x++)
        {
            unsigned int color = pixel(sourceX + x, sourceY + y);
            if (color & 0x000000ff)
            {
                destination->setPixel(destinationX + x, destinationY + y, color);
            }
        }
    }
}

void Texture::fill(unsigned int color)
{
    for (unsigned int y = 0; y != _height; y++)
    {
        for(unsigned int x = 0; x != _width; x++)
        {
            setPixel(x, y, color);
        }
    }
}

std::shared_ptr<Texture> Texture::resize(unsigned int width, unsigned int height)
{
    auto resized = std::shared_ptr<Texture>(new Texture(width, height));

    double _stretch_factor_x = static_cast<double>(width)  / static_cast<double>(this->width());
    double _stretch_factor_y = static_cast<double>(height) / static_cast<double>(this->height());

    //Run across all Y pixels.
    for(unsigned int y = 0; y < this->height(); y++)
    {
        //Run across all X pixels.
        for(unsigned int x = 0; x < this->width(); x++)
        {
            //Draw _stretch_factor_y pixels for each Y pixel.
            for(unsigned int o_y = 0; o_y < _stretch_factor_y; ++o_y)
            {
                //Draw _stretch_factor_x pixels for each X pixel.
                for(unsigned int o_x = 0; o_x < _stretch_factor_x; ++o_x)
                {
                    resized->setPixel(static_cast<unsigned int>(_stretch_factor_x * x) + o_x, static_cast<unsigned int>(_stretch_factor_y * y) + o_y, this->pixel(x, y));
                }
            }
        }
    }
    return resized;
}

std::shared_ptr<Texture> Texture::fitTo(unsigned int width, unsigned int height)
{
    double widthRatio = static_cast<double>(width) / static_cast<double>(this->width());
    double heightRatio = static_cast<double>(height) / static_cast<double>(this->height());

    unsigned int newWidth = static_cast<unsigned int>(static_cast<double>(this->width()) * static_cast<double>(heightRatio));

    if ( newWidth <= width)
    {
        return this->resize(newWidth, height);
    }
    unsigned int newHeight = static_cast<unsigned int>(static_cast<double>(this->height()) * static_cast<double>(widthRatio));

    return this->resize(width, newHeight);
}

}
