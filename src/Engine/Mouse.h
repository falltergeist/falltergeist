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

#ifndef FALLTERGEIST_MOUSE_H
#define FALLTERGEIST_MOUSE_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"
#include "../Engine/ResourceManager.h"

// Third party includes

namespace Falltergeist
{
class Animation;

class Mouse : public Surface
{
protected:
    Animation * _animation = 0;
    int _cursorX = 320;
    int _cursorY = 240;
    int _type = BIG_ARROW;
    int _lastType = BIG_ARROW;
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
          WAIT,
          ACTION,
          ACTION_REVERSE
         };
    enum {ICON_ROTATE = 1,
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
    virtual void think();
    int cursorX();
    int cursorY();
    void setCursorX(int x);
    void setCursorY(int y);
    int type();
    void setType(int type);
    virtual int x();
    virtual int y();
    virtual SDL_Surface* sdl_surface();

};

}

#endif // FALLTERGEIST_MOUSE_H
