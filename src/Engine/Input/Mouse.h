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

#ifndef FALLTERGEIST_MOUSE_H
#define FALLTERGEIST_MOUSE_H

// C++ standard includes
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class UI;

class Mouse
{
protected:    
    int _x = 320;
    int _y = 240;
    bool _visible = true;
    unsigned int _type = NONE;
    std::vector<unsigned int> _states;
    UI* _ui = 0;
    void _setType(unsigned int type);
public:
    enum {
        NONE = 0,
        BIG_ARROW,
        SCROLL_W,
        SCROLL_W_X,
        SCROLL_NW,
        SCROLL_NW_X,
        SCROLL_N,
        SCROLL_N_X,
        SCROLL_NE,
        SCROLL_NE_X,
        SCROLL_E,
        SCROLL_E_X,
        SCROLL_SE,
        SCROLL_SE_X,
        SCROLL_S,
        SCROLL_S_X,
        SCROLL_SW,
        SCROLL_SW_X,
        HEXAGON_RED,
        ACTION,
        ACTION_REVERSE,
        WAIT,
        HAND
    };
    enum {
        ICON_ROTATE = 1,
        ICON_SKILL,
        ICON_INVENTORY,
        ICON_CANCEL,
        ICON_LOOK,
        ICON_TALK,
        ICON_PUSH,
        ICON_UNLOAD,
        ICON_USE
    };
    Mouse();
    ~Mouse();

    int x();
    void setX(int x);

    int y();
    void setY(int y);

    void setState(unsigned int state);
    void pushState(unsigned int state);
    void popState();
    unsigned int state();

    bool scrollState();

    void render();
    void think();

};

}

#endif // FALLTERGEIST_MOUSE_H
