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

#include "../Engine/SurfaceSet.h"

namespace Falltergeist
{

SurfaceSet::SurfaceSet(int x, int y) : InteractiveSurface(0,0,x,y)
{
    _surfaces = new std::vector<Surface *>;
    currentSurface = 0;
}

SurfaceSet::~SurfaceSet()
{
    while (!_surfaces->empty())
    {
        delete _surfaces->back();
        _surfaces->pop_back();
    }
    delete _surfaces;
}

void SurfaceSet::setCurrentSurface(unsigned int number)
{
    currentSurface = number;
}

void SurfaceSet::addSurface(Surface * surface)
{
    _surfaces->push_back(surface);
}

Surface * SurfaceSet::surface()
{
    return new Surface(_surfaces->at(currentSurface));
}

SDL_Surface * SurfaceSet::sdl_surface()
{
    return surface()->sdl_surface();
}


}
