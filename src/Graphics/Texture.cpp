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
#include "../Graphics/Texture.h"

// C++ standard includes

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

using namespace Base;

int NearestPowerOf2(int n)
{
    if (!n) return n; //(0 == 2^0)
    int x = 1;
    while (x < n)
    {
        x <<= 1;
    }
    return x;
}

Texture::Texture(unsigned int width, unsigned int height) : _size(width, height)
{
    _width = width;
    _height = height;

    glGenTextures(1, &_textureID);
}

Texture::Texture(SDL_Surface* surface): _size(surface->w, surface->h)
{
    _width = surface->w;
    _height = surface->h;
    glGenTextures(1, &_textureID);
    loadFromSurface(surface);
}

Texture::~Texture()
{
    if (_textureID > 0)
    {
        glDeleteTextures(1, &_textureID);
        _textureID = 0;
    }
}

unsigned int Texture::width() const
{
    return _width;
}

unsigned int Texture::height() const
{
    return _height;
}

unsigned int Texture::textureWidth() const
{
    return _textureWidth;
}

unsigned int Texture::textureHeight() const
{
    return _textureHeight;
}

Size Texture::size() const
{
    return _size;
}

void Texture::loadFromSurface(SDL_Surface* surface)
{
    SDL_Surface* resizedSurface = NULL;
    SDL_Rect area;

    if (surface == NULL)
    {
        return;
    }

    int newWidth = NearestPowerOf2(_width);
    int newHeight = NearestPowerOf2(_height);

    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;

    SDL_PixelFormatEnumToMasks(
        SDL_PIXELFORMAT_ABGR8888, &bpp,
        &Rmask, &Gmask, &Bmask, &Amask
    );

    resizedSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, bpp,
        Rmask, Gmask, Bmask, Amask
    );

    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;

    SDL_SetSurfaceAlphaMod( surface, 0xFF );
    SDL_SetSurfaceBlendMode( surface, SDL_BLENDMODE_NONE );
    SDL_BlitSurface(surface, &area, resizedSurface, &area);

    glBindTexture(GL_TEXTURE_2D, _textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resizedSurface->w, resizedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, resizedSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    _textureWidth = resizedSurface->w;
    _textureHeight = resizedSurface->h;
    SDL_FreeSurface(resizedSurface);
}

void Texture::loadFromRGB(unsigned int* data)
{
    SDL_Surface* tempSurf = NULL;
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0xff0000;
    gmask = 0x00ff00;
    bmask = 0x0000ff;
    amask = 0x000000;
    tempSurf = SDL_CreateRGBSurfaceFrom(data, _width, _height, 24, _width*3, rmask, gmask, bmask, amask);

    loadFromSurface(tempSurf);

    SDL_FreeSurface(tempSurf);
}

void Texture::loadFromRGBA(unsigned int* data)
{
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;

    SDL_Surface* tempSurf = SDL_CreateRGBSurfaceFrom(data, _width, _height, 32, _width*4, rmask, gmask, bmask, amask);

    loadFromSurface(tempSurf);

    SDL_FreeSurface(tempSurf);
}

void Texture::bind(uint8_t unit)
{
/*    if (unit > GL_MAX_TEXTURE_UNITS)
    {
        // die horribly
        return;
    }
*/
    GLint curunit;
    GLint curtexture;

    if (_textureID > 0)
    {
        glGetIntegerv(GL_ACTIVE_TEXTURE, &curunit);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &curtexture);

        if (curunit != GL_TEXTURE0+unit)
        {
            glActiveTexture(GL_TEXTURE0+unit);
        }
        if (curunit != GL_TEXTURE0+unit || (GLuint)curtexture != _textureID)
        {
            glBindTexture(GL_TEXTURE_2D, _textureID);
        }
    }
}

void Texture::unbind(uint8_t unit)
{
/*    if (unit > GL_MAX_TEXTURE_UNITS)
    {
        // die horribly
        return;
    }
*/
    if (_textureID > 0)
    {
        glActiveTexture(GL_TEXTURE0+unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

bool Texture::opaque(unsigned int x, unsigned int y)
{
    if (x<width() && y<height() && (y*width()+x < _mask.size()))
    {
        return _mask.at(y * width() + x);
    }
    else
    {
        return false;
    }
}

void Texture::setMask(std::vector<bool> mask)
{
    _mask=mask;
}

}
}
