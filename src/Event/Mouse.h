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
#include "../Point.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

class Mouse : public Event
{
public:
    Mouse(const std::string& eventName = "mouse");
    Mouse(const Mouse& event, const std::string& newName);
    Mouse(const Mouse& event);
    ~Mouse() override;

    const Point& position() const;

    void setPosition(const Point& position);

    const Point& offset() const;

    void setOffset(const Point& offset);

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

    Point _position;
    Point _offset;
};

}
}
#endif // FALLTERGEIST_EVENT_MOUSE_H
