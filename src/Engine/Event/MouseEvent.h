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
 */

#ifndef FALLTERGEIST_MOUSEEVENT_H
#define FALLTERGEIST_MOUSEEVENT_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

class MouseEvent : public Event
{
protected:
    unsigned int _x = 0;
    unsigned int _y = 0;
    int _xOffset = 0;
    int _yOffset = 0;
    int _leftButton = false;
    int _rightButton = false;
public:
    MouseEvent(std::string eventName = "mouse");
    MouseEvent(MouseEvent* event);
    virtual ~MouseEvent();

    void setX(unsigned int value);
    unsigned int x();

    void setY(unsigned int value);
    unsigned int y();

    void setXOffset(int value);
    int xOffset();

    void setYOffset(int value);
    int yOffset();

    bool leftButton();
    void setLeftButton(bool value);

    bool rightButton();
    void setRightButton(bool value);
};

}
#endif // FALLTERGEIST_MOUSEEVENT_H
