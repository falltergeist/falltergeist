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

#include "../Engine/Surface.h"

#include "../Engine/CrossPlatform.h"
#include <iostream>

using namespace Falltergeist::CrossPlatform;

namespace Falltergeist
{

Surface::Surface(int width, int height, int x, int y) : _x(x), _y(y), _needRedraw(false), _visible(true)
{
    _borderColor = 0;
    _backgroundColor = 0;
    //                                                                               red         green       blue        alpha
    _sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    clear();
}

Surface::Surface(libfalltergeist::FrmFileType * frm, unsigned int direction, unsigned int frame)
{
    _needRedraw = false;
    _visible = true;
    _borderColor = 0;
    _backgroundColor = 0;

    libfalltergeist::PalFileType * pal = ResourceManager::palFileType("color.pal");

    int width = frm->directions()->at(direction)->frames()->at(frame)->width();
    int height = frm->directions()->at(direction)->frames()->at(frame)->height();
    //                                                                               red         green       blue        alpha
    _sdl_surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    clear();

    int i = 0;
    for (int y = 0; y != height; ++y)
    {
        for (int x = 0; x != width; ++x)
        {
            unsigned int colorIndex = frm->directions()->at(direction)->frames()->at(frame)->colorIndexes()->at(i);
            unsigned int color = *pal->color(colorIndex);
            this->pixel(x, y, color);
            i++;
        }
    }

    int shiftX = frm->directions()->at(direction)->shiftX();
    int offsetX = frm->directions()->at(direction)->frames()->at(frame)->offsetX();
    int shiftY = frm->directions()->at(direction)->shiftY();
    int offsetY = frm->directions()->at(direction)->frames()->at(frame)->offsetY();

    //std::cout <<std::dec << this->x() << ":" << this->y() << std::endl;

    _x = shiftX + offsetX;
    _y = shiftY + offsetY;

    SDL_SetColorKey(this->sdl_surface(), SDL_SRCCOLORKEY, 0);

}


Surface::Surface(Surface * other)
{    
    _sdl_surface = SDL_ConvertSurface(other->sdl_surface(), other->sdl_surface()->format, other->sdl_surface()->flags);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    x(other->x());
    y(other->y());
    visible(other->visible());
    needRedraw(other->needRedraw());

    _backgroundColor = other->_backgroundColor;
    _borderColor = other->_borderColor;
}

Surface::~Surface()
{
    SDL_FreeSurface(sdl_surface());
}

Surface * Surface::needRedraw(bool needRedraw)
{
    _needRedraw = needRedraw;
    return this;
}

bool Surface::needRedraw()
{
    return _needRedraw;
}

Surface * Surface::x(int x)
{
    _x = x;
    return this;
}

int Surface::x()
{
    return _x;
}

Surface * Surface::y(int y)
{
    _y = y;
    return this;
}

int Surface::y()
{
    return _y;
}

unsigned int Surface::width()
{
    return sdl_surface()->w;
}

unsigned int Surface::height()
{
    return sdl_surface()->h;
}

Surface * Surface::clear()
{
    return fill(backgroundColor());
}

SDL_Surface * Surface::sdl_surface()
{
    return _sdl_surface;
}

Surface * Surface::visible(bool visible)
{
    _visible = visible;
    return this;
}

bool Surface::visible()
{
    return (bool)_visible;
}

Surface * Surface::think()
{
    return this;
}

Surface * Surface::draw()
{
    if (!visible()) return this;
    if (!needRedraw()) return this;
    needRedraw(false);
    clear();
    if (_borderColor != 0) _drawBorder();
    return this;
}

Surface * Surface::fill(unsigned int color)
{
    SDL_FillRect(sdl_surface(), NULL, color);
    return this;
}

void Surface::_drawBorder()
{
    for (unsigned int y = 0; y < height(); y++)
    {
        // left border
        pixel(0, y, _borderColor);
        // right border
        pixel(width() - 1, y, _borderColor);
    }
    for (unsigned int x = 0; x < width(); x++)
    {
        // top border
        pixel(x, 0, _borderColor);
        // bottom border
        pixel(x, height() - 1, _borderColor);
    }
}

Surface * Surface::borderColor(unsigned int color)
{
    _borderColor = color;
    return needRedraw(true);
}

unsigned int Surface::borderColor()
{
    return _borderColor;
}

Surface * Surface::backgroundColor(unsigned int color)
{
    _backgroundColor = color;
    return needRedraw(true);
}

unsigned int Surface::backgroundColor()
{
    return _backgroundColor;
}

Surface * Surface::crop(int xOffset, int yOffset, int width, int height)
{
    if (width == 0) width = this->width() - xOffset;
    if (height == 0) height = this->height() - yOffset;

    Surface * surface = new Surface(width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            surface->pixel(x, y, this->pixel(x + xOffset, y + yOffset));
        }
    }
    return surface;
}


Surface * Surface::blit(Surface * surface)
{
    if (!visible()) return this;

    draw();
    SDL_Rect dest = {x(), y(), width(), height()};
    SDL_BlitSurface(this->sdl_surface(), NULL, surface->sdl_surface(), &dest);

    return this;
}

Surface * Surface::copyTo(Surface * surface)
{
    if (!visible()) return this;

    for (unsigned int y = 0; y != height(); ++y)
    {
        for (unsigned int x = 0; x != width(); ++x)
        {
            if (pixel(x, y))
            {
                surface->pixel(x + this->x(), y + this->y(), pixel(x, y));
            }
        }
    }
    return this;
}

unsigned int Surface::pixel(int x, int y)
{
    if (!visible()) return 0;
    // if out of bounds
    if (x < 0 || y < 0 || ((unsigned int) x > width() - 1) || ((unsigned int) y > height() - 1) ) return 0;

    // if empty surface
    if ( width() * height() == 0) return 0;

    // color value
    unsigned int * pixels = (unsigned int *) sdl_surface()->pixels;
    return pixels[(y * width()) + x];
}

Surface * Surface::pixel(int x, int y, unsigned int color)
{
    // lock surface
    if(SDL_MUSTLOCK(sdl_surface())) SDL_LockSurface(sdl_surface());

    // if out of bounds
    if (x < 0 || y < 0 || ((unsigned int) x > width() - 1) || ((unsigned int) y > height() - 1) ) return this;

    // if empty surface
    if ( width() * height() == 0) return this;

    // color value
    unsigned int * pixels = (unsigned int *) sdl_surface()->pixels;
    pixels[(y * width()) + x] = color;

    // unlock surface
    if(SDL_MUSTLOCK(sdl_surface())) SDL_UnlockSurface(sdl_surface());
    return this;
}

Surface * Surface::loadFromSurface(Surface * surface)
{
    SDL_FreeSurface(sdl_surface());
    _sdl_surface = SDL_ConvertSurface(surface->sdl_surface(), surface->sdl_surface()->format, surface->sdl_surface()->flags);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    x(surface->x());
    y(surface->y());
    return this;
}

}
