/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef FALLTERGEIST_SURFACE_H
#define FALLTERGEIST_SURFACE_H

#include <SDL/SDL.h>
#include "../Engine/Exception.h"

namespace Falltergeist
{
class FrmFileType;

class Surface
{
protected:
    SDL_Surface * _sdl_surface;
    int _x; // x position
    int _y; // y position
    bool _visible; // if false - not render
    bool _needRedraw; // surface changed? draw function will be called

    unsigned int _borderColor; // for debugging. @TODO must be removed in future
    unsigned int _backgroundColor; // for debugging @TODO must be removed in future
    void _drawBorder();

public:
    Surface(int width = 0, int height = 0, int x = 0, int y = 0);
    Surface(Surface * other);
    virtual ~Surface();

    Surface * x(int x);
    int x();

    Surface * y(int y);
    int y();

    Surface * needRedraw(bool needRedraw);
    bool needRedraw();

    Surface * visible(bool visible);
    bool visible();

    unsigned int width();    

    unsigned int height();

    Surface * pixel(int x, int y, unsigned int color);
    unsigned int pixel(int x, int y);

    virtual SDL_Surface * sdl_surface();

    Surface * copyTo(Surface * surface);

    Surface * loadFromSurface(Surface * surface);

    Surface * borderColor(unsigned int color);
    unsigned int borderColor();

    Surface * backgroundColor(unsigned int color);
    unsigned int backgroundColor();

    Surface * fill(unsigned int color);
    Surface * clear();
    Surface * crop(int x = 0, int y = 0, int width = 0, int height = 0);
    virtual Surface * think();
    virtual Surface * draw();
    virtual Surface * blit(Surface * surface);
};

}
#endif // FALLTERGEIST_SURFACE_H
