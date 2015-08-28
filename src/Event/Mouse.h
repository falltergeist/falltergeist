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

#ifndef FALLTERGEIST_EVENT_MOUSE_H
#define FALLTERGEIST_EVENT_MOUSE_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

class Mouse : public Event
{
public:
    Mouse(const std::string& eventName = "mouse");
    Mouse(Mouse* event);
    Mouse(Mouse* event, const std::string& name);
    ~Mouse() override;

    unsigned int x() const;
    void setX(unsigned int value);

    unsigned int y() const;
    void setY(unsigned int value);

    int xOffset() const;
    void setXOffset(int value);

    int yOffset() const;
    void setYOffset(int value);

    bool leftButton() const;
    void setLeftButton(bool value);

    bool rightButton() const;
    void setRightButton(bool value);

    bool controlPressed() const;
    void setControlPressed(bool value);

    bool shiftPressed() const;
    void setShiftPressed(bool value);

protected:
    bool _controlPressed = false;
    bool _shiftPressed = false;
    int _leftButton = false;
    int _rightButton = false;
    int _xOffset = 0;
    int _yOffset = 0;
    unsigned int _x = 0;
    unsigned int _y = 0;
};

}
}
#endif // FALLTERGEIST_EVENT_MOUSE_H
