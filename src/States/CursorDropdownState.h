/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include <memory>

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
class Surface;
class HiddenMask;
class GameObject;

class CursorDropdownState : public State
{
protected:
    GameObject* _object;
    int _initialType;
    std::vector<int> _icons;
    int _initialX;
    int _initialY;
    unsigned int _currentSurface = 0;
    std::vector<std::shared_ptr<UI>> _activeIcons;
    std::vector<std::shared_ptr<UI>> _inactiveIcons;
    std::shared_ptr<UI> _surface;
    std::shared_ptr<HiddenMask> _mask;
    std::shared_ptr<UI> _cursor;
public:
    CursorDropdownState(std::vector<int> icons);
    virtual ~CursorDropdownState();
    virtual void init();
    virtual void think();

    void onLeftButtonUp(std::shared_ptr<MouseEvent> event);

    GameObject* object();
    void setObject(GameObject* object);
};

}
#endif // FALLTERGEIST_CURSORDROPDOWNSTATE_H
