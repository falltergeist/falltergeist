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

#include "../Engine/CrossPlatform.h"
#include "../Engine/Screen.h"
#include "../Engine/Surface.h"

using namespace Falltergeist::CrossPlatform;

namespace Falltergeist
{

const double Screen::BASE_WIDTH = 640.0;
const double Screen::BASE_HEIGHT = 480.0;

Screen::Screen(int width, int height, int bpp)
{
    std::cout << "Setting up video mode " << width << "x" << height << "x" << bpp << "...";
    _screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
    SDL_SetAlpha(_screen, SDL_SRCALPHA, 0);
    if (_screen == 0)
    {
        std::cout << "[FAIL]" << std::endl;
    }
    std::cout << "[OK]" << std::endl;

    _surface = new Surface(width,height);
    _surface->backgroundColor(0xFF000000);    
}

Screen::~Screen()
{
    SDL_FreeSurface(_screen);
    delete _surface;
}

Surface * Screen::surface()
{
    return _surface;
}

void Screen::clear()
{
    //_surface->fill(0xFF000000);
    _surface->clear();
}

int Screen::height()
{
    return _screen->h;
}

int Screen::width()
{
    return _screen->w;
}

void Screen::flip()
{
    SDL_BlitSurface(_surface->sdl_surface(), 0, _screen, 0);


    if (SDL_Flip(_screen) == -1)
    {
        std::cout << "[ERROR]Can't flip screen" << std::endl;
        throw Exception(SDL_GetError());
    }
}

}
