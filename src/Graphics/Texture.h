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

#ifndef FALLTERGEIST_GRAPHICS_TEXTURE_H
#define FALLTERGEIST_GRAPHICS_TEXTURE_H

// C++ standard includes
#include <memory>

// Falltergeist includes

// Third party includes
#include "SDL.h"

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

    SDL_Surface* sdlSurface();
    SDL_Texture* sdlTexture();

    void update();

    SDL_Color colorModifier();
    void setColorModifier(SDL_Color color);

    unsigned int width();
    unsigned int height();

    unsigned int pixel(unsigned int x, unsigned int y);
    void setPixel(unsigned int x, unsigned int y, unsigned int color);

    void fill(unsigned int color);

    void copyTo(Texture* destination, unsigned int destinationX = 0, unsigned int destinationY = 0, unsigned int sourceX = 0, unsigned int sourceY = 0, unsigned int sourceWidth = 0, unsigned int sourceHeight = 0);

    Texture* resize(unsigned int width, unsigned int height);
    Texture* fitTo(unsigned int width, unsigned int height);

    void loadFromRGB(unsigned int* data);
    void loadFromRGBA(unsigned int* data);
    void loadFromImage(const std::string& name);

    void setBlendMode(SDL_BlendMode blendMode);
    SDL_BlendMode blendMode();

    bool blitWithAlpha(Texture* blitMask, int maskOffsetX, int maskOffsetY);

    // Helpers to build some specific textures.
    static std::unique_ptr<Texture> generateTextureForNumber(
        unsigned int number,
        unsigned int maxLength,
        Texture* symbolSource,
        unsigned int charWidth,
        unsigned int charHeight,
        unsigned int xOffsetByColor,
        bool isSigned = false);

protected:

    unsigned int _width = 0;
    unsigned int _height = 0;

    SDL_Texture* _sdlTexture = 0;
    SDL_Surface* _sdlSurface = 0;

    SDL_Color _colorModifier = {255, 255, 255, 255};
    SDL_BlendMode _blendMode = SDL_BLENDMODE_BLEND;

    bool _changed = false;

    void _init();
};

}
}
#endif // FALLTERGEIST_GRAPHICS_TEXTURE_H
