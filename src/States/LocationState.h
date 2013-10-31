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
 *
 */

#ifndef FALLTERGEIST_LOCATIONSTATE_H
#define FALLTERGEIST_LOCATIONSTATE_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
class Game;
class Location;
class Animation;
class InteractiveSurface;

class LocationState : public State
{
protected:    
    bool _hexagonalGrid = false;
    Surface * _hexCursor;
    Animation * _animation = 0;
    Location * _location = 0;
    InteractiveSurface * _background;
    unsigned int _direction;
    unsigned int _cameraX;
    unsigned int _cameraY;
    unsigned int _scrollTicks = 0;
    void _drawHexagonalGrid();
public:
    LocationState(Game * game);
    ~LocationState();
    virtual void init();
    virtual void think();
    virtual void blit();

    void onBackgroundClick(Event * event);
    void onKeyboardRelease(Event * event);
};

}

#endif // FALLTERGEIST_LOCATIONSTATE_H
