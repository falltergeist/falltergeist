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

#ifndef FALLTERGEIST_GRAPHICS_TEXTURE_H
#define FALLTERGEIST_GRAPHICS_TEXTURE_H

// C++ standard includes
#include <memory>
#include <vector>

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

// Third party includes
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_opengl.h"

namespace Falltergeist
{
namespace Graphics
{

class Texture
{

public:
    Texture(unsigned int width, unsigned int height);
    Texture(SDL_Surface* surface);
    ~Texture();

    unsigned int width() const;
    unsigned int height() const;

    unsigned int textureWidth() const;
    unsigned int textureHeight() const;

    void loadFromSurface(SDL_Surface* surface);
    void loadFromRGB(unsigned int* data);
    void loadFromRGBA(unsigned int* data);

    void bind(uint8_t unit=0);
    void unbind(uint8_t unit=0);

    bool opaque(unsigned int x, unsigned int y);
    void setMask(std::vector<bool> mask);

    Size size() const;

protected:
    GLuint _textureID;
    unsigned int _width = 0;
    unsigned int _height = 0;
    Size _size;

    unsigned int _textureWidth = 0;
    unsigned int _textureHeight = 0;
    std::vector<bool> _mask;

};

}
}
#endif // FALLTERGEIST_GRAPHICS_TEXTURE_H
