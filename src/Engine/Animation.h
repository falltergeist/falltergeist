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

#ifndef FALLTERGEIST_ANIMATION_H
#define FALLTERGEIST_ANIMATION_H

#include "../Engine/InteractiveSurface.h"
#include <vector>

namespace Falltergeist
{

class Animation : public InteractiveSurface
{   
protected:
    std::vector<std::vector<Surface *> *>  * _surfaceSets;
    unsigned int _frameRate;
    unsigned int _currentFrame;
    unsigned int _currentSurfaceSet;
    unsigned int _lastTicks;
public:
    Animation(const char * filename, int x = 0, int y = 0);
    ~Animation();

    Surface * surface();

    Animation * loadFromFrmFile(const char * filename);
    Animation * think();
};

}
#endif // FALLTERGEIST_ANIMATION_H
