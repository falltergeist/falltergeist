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

#ifndef FALLTERGEIST_SURFACESET_H
#define FALLTERGEIST_SURFACESET_H

#include "../Engine/InteractiveSurface.h"
#include <vector>

namespace Falltergeist
{

class SurfaceSet : public InteractiveSurface
{
protected:
    std::vector<Surface *> * _surfaces;
public:
    SurfaceSet(int x = 0, int y = 0);
    ~SurfaceSet();

    unsigned int currentSurface;
    void addSurface(Surface * surface);
    Surface * surface();
    SDL_Surface * sdl_surface();
};

}
#endif // FALLTERGEIST_SURFACESET_H
