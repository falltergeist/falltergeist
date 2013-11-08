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

#ifndef FALLTERGEIST_CURSORDROPDOWNSTATE_H
#define FALLTERGEIST_CURSORDROPDOWNSTATE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
class Surface;
class HiddenMask;

class CursorDropdownState : public State
{
protected:
    void* _object = 0;
    int _initialType;
    std::vector<int> _icons;
    int _initialX;
    int _initialY;
    int _currentSurface = 0;
    std::vector<Surface*> _activeSurfaces;
    std::vector<Surface*> _inactiveSurfaces;
    Surface* _surface = 0;
    HiddenMask* _mask = 0;
    Surface* _cursor = 0;
public:
    CursorDropdownState(std::vector<int> icons);
    virtual ~CursorDropdownState();
    virtual void init();
    virtual void blit();
    virtual void think();
    void onLeftButtonRelease(Event* event);
    void* object();
    void setObject(void* object);
};

}
#endif // FALLTERGEIST_CURSORDROPDOWNSTATE_H
