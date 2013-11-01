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

#ifndef FALLTERGEIST_SCREEN_H
#define FALLTERGEIST_SCREEN_H

// C++ standard includes
#include <iostream>

// Falltergeist includes

// Third party includes
#include "SDL.h"

namespace Falltergeist
{
class Surface;


class Screen
{
protected:
    SDL_Surface* _screen;
    Surface* _surface;
public:
    Screen(int width, int height, int bpp);
    ~Screen();

    Surface* surface();

    void clear();

    int width();

    int height();

    void flip();
};

}
#endif // FALLTERGEIST_SCREEN_H
