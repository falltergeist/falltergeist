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

#include <SDL/SDL.h>
#include "../Engine/InteractiveSurface.h"
#include "../Engine/ResourceManager.h"

namespace Falltergeist
{

class Mouse : public InteractiveSurface
{
protected:
    int _cursorX;
    int _cursorY;
public:
    enum {BIG_ARROW = 1,
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
          SCROLL_SW_X};
    Mouse();
    ~Mouse();
    virtual void think();
    int cursorX();
    int cursorY();
    void setCursorX(int x);
    void setCursorY(int y);
    void setCursor(unsigned int type);
    virtual int x();
    virtual int y();

};

}

#endif // FALLTERGEIST_MOUSE_H
