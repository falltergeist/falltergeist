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

#ifndef FALLTERGEIST_TEXTURE_H
#define FALLTERGEIST_TEXTURE_H

// C++ standard includes
#include <memory>

// Falltergeist includes

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

class Texture
{
protected:
    unsigned int _id = 0;
    unsigned int _width = 0;
    unsigned int _height = 0;
    unsigned int _texwidth = 0;
    unsigned int _texheight = 0;
    unsigned int* _data = 0; // array of RGBA pixels
    void _unregister();
    SDL_Texture* _sdlTexture = 0;
    SDL_Color _modifier = {255, 255, 255, 255};
public:
    Texture(unsigned int width, unsigned int height);
    virtual ~Texture();

    SDL_Texture* sdlTexture();

    unsigned int id();
    void setId(unsigned int value);

    unsigned int width();
    unsigned int height();
    unsigned int texWidth();
    unsigned int texHeight();
    void texWidth(unsigned int _w);
    void texHeight(unsigned int _h);
    unsigned int* data();

    unsigned int pixel(unsigned int x, unsigned int y);
    void setPixel(unsigned int x, unsigned int y, unsigned int color);

    void fill(unsigned int color);

    void copyTo(Texture* destination, unsigned int destinationX = 0, unsigned int destinationY = 0, unsigned int sourceX = 0, unsigned int sourceY = 0, unsigned int sourceWidth = 0, unsigned int sourceHeight = 0);
    void blitTo(Texture* destination, unsigned int destinationX = 0, unsigned int destinationY = 0, unsigned int sourceX = 0, unsigned int sourceY = 0, unsigned int sourceWidth = 0, unsigned int sourceHeight = 0);

    Texture* resize(unsigned int width, unsigned int height);
    Texture* fitTo(unsigned int width, unsigned int height);

    void loadFromRGB(unsigned int* data);
    void loadFromRGBA(unsigned int* data);

    void setAlpha(unsigned char alpha);
    void setColor(unsigned char r, unsigned char g, unsigned char b);
    unsigned char r();
    unsigned char g();
    unsigned char b();
    unsigned char a();

};

}
#endif // FALLTERGEIST_TEXTURE_H
