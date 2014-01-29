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

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Screen.h"
#include "../Engine/Surface.h"

// Third party includes

namespace Falltergeist
{

Screen::Screen(int width, int height, int bpp)
{
    std::string message = "[VIDEO] - SDL_Init - ";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        debug(message + "[FAIL]", DEBUG_CRITICAL);
        throw Exception(SDL_GetError());
    }
    debug(message + "[OK]", DEBUG_INFO);
    
    message =  "[VIDEO] - SDL_SetVideoMode " + std::to_string(width) + "x" + std::to_string(height) + "x" +std::to_string(bpp)+ " - ";
    _screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (!_screen)
    {
        throw Exception(message + "[FAIL]");
    }
    debug(message + "[OK]", DEBUG_INFO);

    _surface = new Surface(width, height);
    _surface->setBackgroundColor(0xFF000000);
}

Screen::~Screen()
{
    SDL_FreeSurface(_screen);
    delete _surface;
}

Surface* Screen::surface()
{
    return _surface;
}

void Screen::clear()
{
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
        debug("[VIDEO] - Can't flip screen", DEBUG_CRITICAL);
        throw Exception(SDL_GetError());
    }
}

}
