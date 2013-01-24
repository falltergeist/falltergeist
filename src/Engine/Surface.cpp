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
#include "../Fallout/FrmFileType.h"

namespace Falltergeist
{

Surface::Surface(int width, int height, int x, int y) : _x(x), _y(y)
{
    needRedraw = false;
    _visible = true;
    _borderColor = 0;
    _backgroundColor = 0;
    _surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (_surface == 0) throw Exception(SDL_GetError());
    clear();
}

Surface::Surface(Surface * other)
{    
    _surface = SDL_ConvertSurface(other->_surface, other->_surface->format, other->_surface->flags);
    if (_surface == 0) throw Exception(SDL_GetError());
    _x = other->_x;
    _y = other->_y;
    _visible = other->_visible;
    _backgroundColor = other->_backgroundColor;
    needRedraw = other->needRedraw;
    _borderColor = other->_borderColor;
}

Surface::~Surface()
{
    SDL_FreeSurface(_surface);
}

int Surface::getX()
{
    return _x;
}

int Surface::getY()
{
    return _y;
}

unsigned int Surface::getWidth()
{
    return _surface->w;
}

unsigned int Surface::getHeight()
{
    return _surface->h;
}

void Surface::setX(int x)
{
    _x = x;
}

void Surface::setY(int y)
{
    _y = y;
}

void Surface::clear()
{
    fill(_backgroundColor);
}

SDL_Surface * Surface::getSurface()
{
    draw();
    return _surface;
}

void Surface::hide()
{
    _visible = false;
}

void Surface::show()
{
    _visible = true;
}

void Surface::think()
{
}

void Surface::draw()
{
    if (needRedraw == false) return;
    needRedraw = false;
    clear();
    if (_borderColor != 0) _drawBorder();
}

void Surface::fill(unsigned int color)
{
    SDL_FillRect(_surface, NULL, color);
}

void Surface::_drawBorder()
{
    _lock();
    unsigned int * pixels = (unsigned int *) _surface->pixels;
    for (unsigned int y = 0; y < getHeight(); y++)
    {
        pixels[(y * _surface->w)] = _borderColor;
        pixels[(y * _surface->w) + _surface->w - 1] = _borderColor;
    }
    for (unsigned int x = 0; x < getWidth(); x++)
    {
        pixels[1 + x] = _borderColor;
        pixels[_surface->w * (_surface->h - 1) + x] = _borderColor;
    }
    _unlock();
}

void Surface::setBorderColor(unsigned int color)
{
    _borderColor = color;
    needRedraw= true;
}

unsigned int Surface::getBorderColor()
{
    return _borderColor;
}

void Surface::setBackgroundColor(unsigned int color)
{
    _backgroundColor = color;
    needRedraw = true;
}

unsigned int Surface::getBackgroundColor()
{
    return _backgroundColor;
}

Surface * Surface::crop(int xOffset, int yOffset, int width, int height)
{
    if (width == 0) width = getWidth() - xOffset;
    if (height == 0) height = getHeight() - yOffset;

    Surface * surface = new Surface(width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            surface->setPixel(x, y, this->getPixel(x + xOffset, y + yOffset));
        }
    }
    return surface;
}

void Surface::blit(Surface * surface)
{
    if (_visible)
    {
        SDL_Rect dest;
        dest.x = _x;
        dest.y = _y;
        SDL_BlitSurface(getSurface(), NULL, surface->getSurface(), &dest);
    }
    else
    {
        getSurface();
    }
}

void Surface::copyTo(Surface * surface)
{
    _lock();
    unsigned int * thisPixels = (unsigned int *) _surface->pixels;
    unsigned int * thatPixels = (unsigned int *) surface->_surface->pixels;
    for (unsigned int y = 0; y < getHeight(); y++)
    {
        for (unsigned int x = 0; x < getWidth(); x++)
        {
            thatPixels[((y + _y) * surface->_surface->w) + x + _x] = thisPixels[(y * _surface->w) + x];
        }
    }
    _unlock();
}

unsigned int Surface::getPixel(int x, int y)
{
    _lock();
    if (x < 0 || y < 0) return 0;
    if ((unsigned int) x > getWidth() || (unsigned int) y > getHeight()) return 0;
    if (getWidth()*getHeight() == 0) return 0;

    unsigned int * pixels = (unsigned int *) _surface->pixels;
    unsigned int color = pixels[(y * _surface->w) + x];
    _unlock();
    return color;
}

void Surface::setPixel(int x, int y, unsigned int color)
{
    _lock();
    if (x < 0 || y < 0) return;
    if ((unsigned int) x > getWidth() || (unsigned int) y > getHeight()) return;

    unsigned int * pixels = (unsigned int *) _surface->pixels;
    pixels[(y * _surface->w) + x] = color;
    _unlock();
}

void Surface::_lock()
{
    if(SDL_MUSTLOCK(_surface)) SDL_LockSurface(_surface);
}

void Surface::_unlock()
{
    if(SDL_MUSTLOCK(_surface)) SDL_UnlockSurface(_surface);
}

void Surface::loadFromSurface(Surface * surface)
{
    SDL_FreeSurface(_surface);
    _surface = surface->getSurface();
    _x = surface->getX();
    _y = surface->getY();
}

}
