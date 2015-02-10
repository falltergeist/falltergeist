/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_KEYBOARDEVENT_H
#define FALLTERGEIST_KEYBOARDEVENT_H

// C++ standard includes

// Falltergeist includes
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

class KeyboardEvent : public Event
{
protected:
    int _keyCode = 0;
    bool _shiftPressed = false;
    bool _controlPressed = false;
public:
    KeyboardEvent(std::string name = "keyboard");
    virtual ~KeyboardEvent();
    int keyCode();
    void setKeyCode(int value);
    bool shiftPressed();
    void setShiftPressed(bool value);
    bool controlPressed();
    void setControlPressed(bool value);
};

}
#endif // FALLTERGEIST_KEYBOARDEVENT_H
