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

namespace Falltergeist
{

Surface::Surface(int width, int height, int x, int y) : _x(x), _y(y), _needRedraw(false), _visible(true)
{
    _borderColor = 0;
    _backgroundColor = 0;
    //                                                                               red         green       blue        alpha
    _surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (_surface == 0) throw Exception(SDL_GetError());
    clear();
}

Surface::Surface(Surface * other)
{    
    _surface = SDL_ConvertSurface(other->_surface, other->_surface->format, other->_surface->flags);
    if (_surface == 0) throw Exception(SDL_GetError());
    setX(other->x());
    setY(other->y());
    setVisible(other->visible());
    setNeedRedraw(other->needRedraw());

    _backgroundColor = other->_backgroundColor;
    _borderColor = other->_borderColor;
}

Surface::~Surface()
{
    SDL_FreeSurface(_surface);
}

/**
 * Sets if redraw needed
 * @brief Surface::setNeedRedraw
 * @param needRedraw
 */
void Surface::setNeedRedraw(bool needRedraw)
{
    _needRedraw = needRedraw;
}

/**
 * Redraw needed?
 * @brief Surface::needRedraw
 * @return
 */
bool Surface::needRedraw()
{
    return _needRedraw;
}

/**
 * Sets surface x position
 * @brief Surface::setX
 * @param x
 */
void Surface::setX(int x)
{
    _x = x;
}

/**
 * Returns surface x position
 * @brief Surface::x
 * @return
 */
int Surface::x()
{
    return _x;
}

/**
 * Sets surface y position
 * @brief Surface::setY
 * @param y
 */
void Surface::setY(int y)
{
    _y = y;
}

/**
 * Returns surface y position
 * @brief Surface::y
 * @return
 */
int Surface::y()
{
    return _y;
}

/**
 * Returns surface width
 * @brief Surface::width
 * @return
 */
unsigned int Surface::width()
{
    return _surface->w;
}

/**
 * Returns surface height
 * @brief Surface::height
 * @return
 */
unsigned int Surface::height()
{
    return _surface->h;
}

/**
 * Clears surface
 * @brief Surface::clear
 */
void Surface::clear()
{
    fill(backgroundColor());
}

/**
 * Returns SDL_Surface structure
 * @brief Surface::surface
 * @return
 */
SDL_Surface * Surface::surface()
{
    draw();
    return _surface;
}

/**
 * Sets if surface is visible
 * @brief Surface::setVisible
 * @param visible
 */
void Surface::setVisible(bool visible)
{
    _visible = visible;
}

/**
 * Returns if surface is visible
 * @brief Surface::visible
 * @return
 */
bool Surface::visible()
{
    return _visible;
}

/**
 * Some actions here
 * @brief Surface::think
 */
void Surface::think()
{
}

/**
 * Draws the surface
 * @brief Surface::draw
 */
void Surface::draw()
{
    if (!needRedraw()) return;
    setNeedRedraw(false);
    clear();
    if (_borderColor != 0) _drawBorder();
}

/**
 * Fills surface with color
 * @brief Surface::fill
 * @param color
 */
void Surface::fill(unsigned int color)
{
    SDL_FillRect(_surface, NULL, color);
}

/**
 * Draws border
 * @brief Surface::_drawBorder
 */
void Surface::_drawBorder()
{
    for (unsigned int y = 0; y < height(); y++)
    {
        // left border
        setPixel(0, y, _borderColor);
        // right border
        setPixel(width() - 1, y, _borderColor);
    }
    for (unsigned int x = 0; x < width(); x++)
    {
        // top border
        setPixel(x, 0, _borderColor);
        // bottom border
        setPixel(x, height() - 1, _borderColor);
    }
}

/**
 * Sets border color
 * @brief Surface::setBorderColor
 * @param color
 */
void Surface::setBorderColor(unsigned int color)
{
    _borderColor = color;
    setNeedRedraw(true);
}

/**
 * Returns border color
 * @brief Surface::borderColor
 * @return
 */
unsigned int Surface::borderColor()
{
    return _borderColor;
}

/**
 * Sets background color
 * @brief Surface::setBackgroundColor
 * @param color
 */
void Surface::setBackgroundColor(unsigned int color)
{
    _backgroundColor = color;
    setNeedRedraw(true);
}

/**
 * Returns background color
 * @brief Surface::backgroundColor
 * @return
 */
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
            surface->setPixel(x, y, this->pixel(x + xOffset, y + yOffset));
        }
    }
    return surface;
}


void Surface::blit(Surface * surface)
{
    if (visible())
    {
        SDL_Rect dest;
        dest.x = x();
        dest.y = y();
        SDL_BlitSurface(this->surface(), NULL, surface->surface(), &dest);
    }
    else
    {
        this->surface();
    }
}

void Surface::copyTo(Surface * surface)
{
    for (unsigned int y = 0; y != height(); ++y)
    {
        for (unsigned int x = 0; x != width(); ++x)
        {
            if (pixel(x, y))
            {
                surface->setPixel(x + this->x(), y + this->y(), pixel(x, y));
            }
        }
    }
}

/**
 * Returns pixel color
 * @brief Surface::pixel
 * @param x
 * @param y
 * @return
 */
unsigned int Surface::pixel(int x, int y)
{
    // if out of bounds
    if (x < 0 || y < 0 || ((unsigned int) x > width() - 1) || ((unsigned int) y > height() - 1) ) return 0;

    // if empty surface
    if ( width() * height() == 0) return 0;

    // color value
    unsigned int * pixels = (unsigned int *) _surface->pixels;
    return pixels[(y * _surface->w) + x];
}

/**
 * Sets pixel color
 * @brief Surface::setPixel
 * @param x
 * @param y
 * @param color
 */
void Surface::setPixel(int x, int y, unsigned int color)
{
    // lock surface
    if(SDL_MUSTLOCK(_surface)) SDL_LockSurface(_surface);

    // if out of bounds
    if (x < 0 || y < 0 || ((unsigned int) x > width() - 1) || ((unsigned int) y > height() - 1) ) return;

    // if empty surface
    if ( width() * height() == 0) return;

    // color value
    unsigned int * pixels = (unsigned int *) _surface->pixels;
    pixels[(y * _surface->w) + x] = color;

    // unlock surface
    if(SDL_MUSTLOCK(_surface)) SDL_UnlockSurface(_surface);
}

/**
 * Loads surface data from other surface
 * @brief Surface::loadFromSurface
 * @param surface
 */
void Surface::loadFromSurface(Surface * surface)
{
    SDL_FreeSurface(_surface);
    _surface = SDL_ConvertSurface(surface->_surface, surface->_surface->format, surface->_surface->flags);
    if (_surface == 0) throw Exception(SDL_GetError());
    setX(surface->x());
    setY(surface->y());
}

}
