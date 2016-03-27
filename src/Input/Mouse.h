/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_INPUT_MOUSE_H
#define FALLTERGEIST_INPUT_MOUSE_H

// C++ standard includes
#include <memory>
#include <vector>

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
    class Base;
}
namespace Input
{

using Graphics::Point;

class Mouse
{
public:
    // TODO: need to consider getting rid of mouse cursor state stack, it's not convenient to use
    enum class Cursor : unsigned
    {
        NONE           = 0,
        BIG_ARROW      = 1,
        SCROLL_W       = 2,
        SCROLL_W_X     = 3,
        SCROLL_NW      = 4,
        SCROLL_NW_X    = 5,
        SCROLL_N       = 6,
        SCROLL_N_X     = 7,
        SCROLL_NE      = 8,
        SCROLL_NE_X    = 9,
        SCROLL_E       = 10,
        SCROLL_E_X     = 11,
        SCROLL_SE      = 12,
        SCROLL_SE_X    = 13,
        SCROLL_S       = 14,
        SCROLL_S_X     = 15,
        SCROLL_SW      = 16,
        SCROLL_SW_X    = 17,
        HEXAGON_RED    = 18,
        ACTION         = 19,
        ACTION_REVERSE = 20,
        WAIT           = 21,
        HAND           = 22,
        SMALL_UP_ARROW = 23,
        SMALL_DOWN_ARROW = 24
    };
    // TODO: this is specific to CursorDropdown state, should not be here
    enum class Icon : unsigned
    {
        ROTATE = 1,
        SKILL,
        INVENTORY,
        CANCEL,
        LOOK,
        TALK,
        PUSH,
        UNLOAD,
        USE
    };
    Mouse();
    ~Mouse();

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    const Point& position() const;
    void setPosition(const Point& pos);

    void pushState(Cursor state);
    void popState();

    Cursor state() const;
    void setState(Cursor state);

    // todo: probably need to remove this (engine should not be directly tied to Lua)
    unsigned cursor() const; // for lua sripts
    void setCursor(unsigned value); // for lua scripts

    std::vector<Cursor>* states();

    bool scrollState();

    void render();
    void renderOutline();
    void think();

    UI::Base* ui();

protected:
    Point _position {320, 240};
    bool _visible = true;
    Cursor _type = Cursor::NONE;
    std::vector<Cursor> _states;
    std::unique_ptr<UI::Base> _ui;
    void _setType(Cursor type);
};

}
}
#endif // FALLTERGEIST_INPUT_MOUSE_H
