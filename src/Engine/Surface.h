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
    SDL_Surface * _surface;
    bool _visible;
    int _x;
    int _y;
    unsigned int _borderColor;
    unsigned int _backgroundColor;
    void _lock();
    void _unlock();
    void _drawBorder();
public:
    bool needRedraw;
    Surface(int width = 0, int height = 0, int x = 0, int y = 0);
    Surface(Surface * other);
    virtual ~Surface();
    int getX();
    int getY();
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getPixel(int x, int y);
    virtual SDL_Surface * getSurface();
    void copyTo(Surface * surface);
    void setPixel(int x, int y, unsigned int color);
    void loadFromSurface(Surface * surface);
    void show();
    void hide();
    void setX(int x);
    void setY(int y);
    void fill(unsigned int color);
    void border(unsigned int color);
    void setBorderColor(unsigned int color);
    unsigned int getBorderColor();
    void setBackgroundColor(unsigned int color);
    unsigned int getBackgroundColor();
    void clear();
    Surface * crop(int x = 0, int y = 0, int width = 0, int height = 0);
    virtual void think();
    virtual void draw();
    virtual void blit(Surface * surface);
};

}
#endif // FALLTERGEIST_SURFACE_H
