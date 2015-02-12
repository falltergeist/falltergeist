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
#include "../Graphics/Texture.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Exception.h"

// Third party includes

namespace Falltergeist
{

Texture::Texture(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    _init();
}

Texture::Texture(SDL_Surface* surface)
{
    _width = surface->w;
    _height = surface->h;
    _init();
    loadFromRGBA((unsigned int*)surface->pixels);
}

Texture::~Texture()
{
    SDL_FreeSurface(_sdlSurface);
    SDL_DestroyTexture(_sdlTexture);
}

void Texture::_init()
{
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER != SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    _sdlSurface = SDL_CreateRGBSurface(0, width(), height(), 32, rmask, gmask, bmask, amask);
    if(!_sdlSurface)
    {
        throw Exception(SDL_GetError());
    }

    SDL_SetSurfaceBlendMode(_sdlSurface, SDL_BLENDMODE_BLEND);

    _sdlTexture = SDL_CreateTexture(Game::getInstance()->renderer()->sdlRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width(), height());
    if(!_sdlTexture)
    {
        throw Exception(SDL_GetError());
    }

    setBlendMode(_blendMode);
    setColorModifier(_colorModifier);
}

unsigned int Texture::width()
{
    return _width;
}

unsigned int Texture::height()
{
    return _height;
}

unsigned int Texture::pixel(unsigned int x, unsigned int y)
{
    if (x >= _width || y >= _height) return 0;

    unsigned int pixel = 0;

    if (SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_LockSurface(_sdlSurface);
    }

    unsigned int* pixels = (unsigned int*)_sdlSurface->pixels;
    pixel = pixels[(y * width()) + x];

    if(SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_UnlockSurface(_sdlSurface);
    }

    return pixel;
}

void Texture::setPixel(unsigned int x, unsigned int y, unsigned int color)
{
    if (x >= _width || y >= _height) return;

    if (SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_LockSurface(_sdlSurface);
    }

    unsigned int* pixels = (unsigned int*)_sdlSurface->pixels;
    pixels[(y * width()) + x] = color;

    if(SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_UnlockSurface(_sdlSurface);
    }

    _changed = true;
}

void Texture::loadFromRGB(unsigned int* data)
{
    if (SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_LockSurface(_sdlSurface);
    }

    unsigned int* pixels = (unsigned int*)_sdlSurface->pixels;

    for (unsigned int i = 0; i != width()*height(); ++i)
    {
        pixels[i] = (data[i] << 8) | 0xFF;
    }

    if(SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_UnlockSurface(_sdlSurface);
    }

    _changed = true;
}

void Texture::loadFromRGBA(unsigned int* data)
{
    if (SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_LockSurface(_sdlSurface);
    }

    unsigned int* pixels = (unsigned int*)_sdlSurface->pixels;

    for (unsigned int i = 0; i != width()*height(); ++i)
    {
        pixels[i] = data[i];
    }

    if(SDL_MUSTLOCK(_sdlSurface))
    {
        SDL_UnlockSurface(_sdlSurface);
    }

    _changed = true;
}

void Texture::copyTo(Texture* destination, unsigned int destinationX, unsigned int destinationY, unsigned int sourceX, unsigned int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    if (sourceWidth == 0)
    {
        sourceWidth = width();
    }

    if (sourceHeight == 0)
    {
        sourceHeight = height();
    }

    // @fixme: optimize this section
    for (unsigned int y = 0; y != sourceHeight; y++)
    {
        for(unsigned int x = 0; x != sourceWidth; x++)
        {
            destination->setPixel(destinationX + x, destinationY + y, pixel(sourceX + x, sourceY + y));
        }
    }
}

void Texture::blitTo(Texture* destination, unsigned int destinationX, unsigned int destinationY, unsigned int sourceX, unsigned int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    if (sourceWidth == 0)
    {
        sourceWidth = width();
    }

    if (sourceHeight == 0)
    {
        sourceHeight = height();
    }

    // @fixme: optimize this section
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
    // @fixme: SDL_FillRect must be used
    for (unsigned int y = 0; y != _height; y++)
    {
        for(unsigned int x = 0; x != _width; x++)
        {
            setPixel(x, y, color);
        }
    }
    _changed = true;
}

Texture* Texture::resize(unsigned int width, unsigned int height)
{
    auto resized = new Texture(width, height);

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

Texture* Texture::fitTo(unsigned int width, unsigned int height)
{
    double widthRatio = static_cast<double>(width) / static_cast<double>(this->width());
    double heightRatio = static_cast<double>(height) / static_cast<double>(this->height());

    unsigned int newWidth = static_cast<unsigned int>(static_cast<double>(this->width()) * static_cast<double>(heightRatio));

    if (newWidth <= width)
    {
        return this->resize(newWidth, height);
    }
    unsigned int newHeight = static_cast<unsigned int>(static_cast<double>(this->height()) * static_cast<double>(widthRatio));

    return this->resize(width, newHeight);
}

SDL_Surface* Texture::sdlSurface()
{
    return _sdlSurface;
}

SDL_Texture* Texture::sdlTexture()
{
    if (_changed)
    {
        SDL_UpdateTexture(_sdlTexture, NULL, _sdlSurface->pixels, _sdlSurface->pitch);
        _changed = false;

    }
    return _sdlTexture;
}

SDL_Color Texture::colorModifier()
{
    return _colorModifier;
}

void Texture::setColorModifier(SDL_Color color)
{
    _colorModifier = color;
    SDL_SetTextureColorMod(_sdlTexture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(_sdlTexture, color.a);
}

void Texture::setBlendMode(SDL_BlendMode blendMode)
{
    _blendMode = blendMode;
    SDL_SetTextureBlendMode(_sdlTexture, _blendMode);
}

SDL_BlendMode Texture::blendMode()
{
    return _blendMode;
}

}
