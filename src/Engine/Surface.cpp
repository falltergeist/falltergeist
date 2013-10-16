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

// C++ standard includes
#include <iostream>

// Falltergeist includes
#include "../Engine/Surface.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/AnimatedPalette.h"

// Third party includes

using namespace Falltergeist::CrossPlatform;

namespace Falltergeist
{

AnimatedPalette * Surface::animatedPalette = new AnimatedPalette();

Surface::Surface(int width, int height, int x, int y) : _x(x), _y(y), _needRedraw(false), _visible(true)
{
    _animatedPixels = 0;
    _borderColor = 0;
    _backgroundColor = 0;
    setXOffset(0);
    setYOffset(0);
    //                                                                               red         green       blue        alpha
    _sdl_surface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    clear();
}

Surface::Surface(libfalltergeist::FrmFileType * frm, unsigned int direction, unsigned int frame)
{
    _animatedPixels = 0;
    _needRedraw = false;
    _visible = true;
    _borderColor = 0;
    _backgroundColor = 0;

    libfalltergeist::PalFileType * pal = ResourceManager::palFileType("color.pal");

    int width = frm->directions()->at(direction)->frames()->at(frame)->width();
    int height = frm->directions()->at(direction)->frames()->at(frame)->height();
    //                                                                               red         green       blue        alpha
    _sdl_surface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    clear();

    int i = 0;
    for (int y = 0; y != height; ++y)
    {
        for (int x = 0; x != width; ++x)
        {
            unsigned int colorIndex = frm->directions()->at(direction)->frames()->at(frame)->colorIndexes()->at(i);

            if (colorIndex >= 229 && colorIndex <= 254)
            {
                    if (_animatedPixels == 0) _animatedPixels = new std::vector<unsigned int>;
                    _animatedPixels->push_back(x);
                    _animatedPixels->push_back(y);
                    _animatedPixels->push_back(colorIndex);
            }
            else
            {
                    unsigned int color = *pal->color(colorIndex);
                    this->setPixel(x, y, color);                
            }
            i++;
        }
    }

    int shiftX = frm->directions()->at(direction)->shiftX();
    int offsetX = frm->directions()->at(direction)->frames()->at(frame)->offsetX();
    int shiftY = frm->directions()->at(direction)->shiftY();
    int offsetY = frm->directions()->at(direction)->frames()->at(frame)->offsetY();

    setX(0);
    setY(0);
    setXOffset(shiftX + offsetX);
    setYOffset(shiftY + offsetY);

    SDL_SetColorKey(this->sdl_surface(), SDL_RLEACCEL | SDL_SRCCOLORKEY, 0);

}


Surface::Surface(Surface * other)
{
    _animatedPixels = 0;

    if (other->_animatedPixels != 0)
    {
        _animatedPixels = new std::vector<unsigned int>;
        for (std::vector<unsigned int>::iterator it = other->_animatedPixels->begin(); it != other->_animatedPixels->end(); ++it)
        {
            _animatedPixels->push_back(*it);
        }

    }

    _sdl_surface = SDL_ConvertSurface(other->sdl_surface(), other->sdl_surface()->format, other->sdl_surface()->flags);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());
    setX(other->x());
    setY(other->y());
    setXOffset(other->xOffset());
    setYOffset(other->yOffset());
    setVisible(other->visible());
    setNeedRedraw(other->needRedraw());

    _backgroundColor = other->_backgroundColor;
    _borderColor = other->_borderColor;
}

Surface::~Surface()
{
    SDL_FreeSurface(sdl_surface());
    delete _animatedPixels;
}

void Surface::setNeedRedraw(bool needRedraw)
{
    _needRedraw = needRedraw;
}

bool Surface::needRedraw()
{
    return _needRedraw;
}

void Surface::setX(int x)
{
    _x = x;
}

int Surface::x()
{
    return _x;
}

void Surface::setXOffset(int offset)
{
    _xOffset = offset;
}

int Surface::xOffset()
{
    return _xOffset;
}


void Surface::setY(int y)
{
    _y = y;
}

int Surface::y()
{
    return _y;
}

void Surface::setYOffset(int offset)
{
    _yOffset = offset;
}

int Surface::yOffset()
{
    return _yOffset;
}

unsigned int Surface::width()
{
    return sdl_surface()->w;
}

unsigned int Surface::height()
{
    return sdl_surface()->h;
}

void Surface::clear()
{
    fill(backgroundColor());
}

SDL_Surface * Surface::sdl_surface()
{
    return _sdl_surface;
}

void Surface::setVisible(bool visible)
{
    _visible = visible;
}

bool Surface::visible()
{
    return (bool)_visible;
}

void Surface::think()
{
}

void Surface::draw()
{
    if (!visible()) return;

    if (_animatedPixels != 0)
    {
        for (std::vector<unsigned int>::iterator it = _animatedPixels->begin(); it != _animatedPixels->end(); it += 3)
        {
            setPixel(*(it), *(it+1), animatedPalette->color(*(it+2)));
        }
    }

    if (!needRedraw()) return;
    setNeedRedraw(false);
    clear();
    if (_borderColor != 0) _drawBorder();
}

void Surface::fill(unsigned int color)
{
    SDL_FillRect(sdl_surface(), NULL, color);
    delete _animatedPixels;
    _animatedPixels = 0;
}

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

void Surface::setBorderColor(unsigned int color)
{
    _borderColor = color;
    setNeedRedraw(true);
}

unsigned int Surface::borderColor()
{
    return _borderColor;
}

void Surface::setBackgroundColor(unsigned int color)
{
    _backgroundColor = color;
    setNeedRedraw(true);
}

unsigned int Surface::backgroundColor()
{
    return _backgroundColor;
}

Surface * Surface::crop(int xOffset, int yOffset, int width, int height)
{
    if (width  == 0) width  = this->width()  - xOffset;
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
    if (!visible()) return;
    draw();

    if (this->x() + this->xOffset() + this->width() < 0 && this->y() + this->yOffset() + this->height() < 0) return;

    SDL_Rect dest = {x() + xOffset(), y() + yOffset(), width(), height()};
    SDL_BlitSurface(this->sdl_surface(), NULL, surface->sdl_surface(), &dest);

    _copyAnimatedPixelsTo(surface);
}

void Surface::_copyAnimatedPixelsFrom(Surface * surface)
{
    delete _animatedPixels;
    _animatedPixels = 0;
    if (surface->_animatedPixels != 0)
    {
        _animatedPixels = new std::vector<unsigned int>;
        for (std::vector<unsigned int>::iterator it = surface->_animatedPixels->begin(); it != surface->_animatedPixels->end(); ++it)
        {
            _animatedPixels->push_back(*it);
        }
    }
}

void Surface::_copyAnimatedPixelsTo(Surface * surface)
{
    if (_animatedPixels != 0)
    {
        if (surface->_animatedPixels == 0) surface->_animatedPixels = new std::vector<unsigned int>;
        for (std::vector<unsigned int>::iterator it = _animatedPixels->begin(); it != _animatedPixels->end(); it += 3)
        {
            surface->_animatedPixels->push_back(*(it) + this->x() + this->xOffset());
            surface->_animatedPixels->push_back(*(it+1) + this->y() + this->yOffset());
            surface->_animatedPixels->push_back(*(it+2));
        }
    }
}

void Surface::copyTo(Surface * surface)
{
    if (!visible()) return;
    draw();    

    if (this->x() + this->xOffset() + this->width() < 0 && this->y() + this->yOffset() + this->height() < 0) return;

    for (unsigned int y = 0; y != height(); ++y)
    {
        for (unsigned int x = 0; x != width(); ++x)
        {
            if (pixel(x, y))
            {
                surface->setPixel(x + this->x() + this->xOffset(), y + this->y() + this->yOffset(), pixel(x, y));
            }
        }
    }
    _copyAnimatedPixelsTo(surface);
}

unsigned int Surface::pixel(int x, int y)
{
    if (!visible()) return 0;

    // if out of bounds
    if (x < 0 || y < 0 || (x > width() - 1) || (y > height() - 1) ) return 0;
    // if empty surface
    if ( width()*height() == 0) return 0;

    if(SDL_MUSTLOCK(sdl_surface())) SDL_LockSurface(sdl_surface());

    // color value
    unsigned int * pixels = (unsigned int *) sdl_surface()->pixels;
    unsigned int index = (y * width()) + x;

    if (!pixels) return 0;

    unsigned int pixel = pixels[index];

    if(SDL_MUSTLOCK(sdl_surface())) SDL_UnlockSurface(sdl_surface());

    return pixel;
}

void Surface::setPixel(int x, int y, unsigned int color)
{
    // if out of bounds
    if (x < 0 || y < 0 || (x > width() - 1) || (y > height() - 1)) return;
    // if empty surface
    if ( width()*height() == 0) return;

    // color value
    unsigned int * pixels = (unsigned int *) sdl_surface()->pixels;
    pixels[(y * width()) + x] = color;
}

void Surface::loadFromSurface(Surface * surface)
{
    SDL_FreeSurface(sdl_surface());
    _sdl_surface = SDL_ConvertSurface(surface->sdl_surface(), surface->sdl_surface()->format, surface->sdl_surface()->flags);
    if (sdl_surface() == 0) throw Exception(SDL_GetError());

    _copyAnimatedPixelsFrom(surface);

    setX(surface->x());
    setY(surface->y());
    setXOffset(surface->xOffset());
    setYOffset(surface->yOffset());
}

}
