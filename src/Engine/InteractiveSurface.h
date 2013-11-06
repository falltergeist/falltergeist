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
 */

#ifndef FALLTERGEIST_INTERACTIVESURFACE_H
#define FALLTERGEIST_INTERACTIVESURFACE_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/State.h"
#include "../Engine/Surface.h"
#include "../Engine/Event.h"

// Third party includes

namespace Falltergeist
{

typedef void (State::*EventHandler)(Event*);

class InteractiveSurface : public Surface
{
protected:
    bool _hovered = false;
    bool _drag = false;
    bool _leftButtonPressed = false;
    bool _rightButtonPressed = false;
    EventHandler _onMouseIn = 0;
    EventHandler _onMouseOut = 0;
    EventHandler _onMouseOver = 0;
    EventHandler _onDragStart = 0;
    EventHandler _onDragStop = 0;
    EventHandler _onDrag = 0;
    EventHandler _onLeftButtonPress = 0;
    EventHandler _onLeftButtonRelease = 0;
    EventHandler _onLeftButtonClick = 0;
    EventHandler _onRightButtonRelease = 0;
    EventHandler _onRightButtonPress = 0;
    EventHandler _onRightButtonClick = 0;
    EventHandler _onKeyboardPress = 0;
    EventHandler _onKeyboardRelease = 0;
public:
    InteractiveSurface(libfalltergeist::FrmFileType* frm, unsigned int direction = 0, unsigned int frame = 0);
    InteractiveSurface(int width = 0, int height = 0, int x = 0, int y = 0);
    InteractiveSurface(Surface* other);
    virtual ~InteractiveSurface();
    virtual void handle(Event* event, State* state);
    virtual void mouseIn(Event* event, State* state);
    virtual void mouseOver(Event* event, State* state);
    virtual void mouseOut(Event* event, State* state);
    virtual void dragStart(Event* event, State* state);
    virtual void dragStop(Event* event, State* state);
    virtual void drag(Event* event, State* state);
    virtual void leftButtonPress(Event* event, State* state);
    virtual void leftButtonRelease(Event* event, State* state);
    virtual void leftButtonClick(Event* event, State* state);
    virtual void rightButtonPress(Event* event, State* state);
    virtual void rightButtonRelease(Event* event, State* state);
    virtual void rightButtonClick(Event* event, State* state);
    virtual void keyboardPress(Event* event, State* state);
    virtual void keyboardRelease(Event* event, State* state);
    virtual void onMouseIn(EventHandler handler);
    virtual void onMouseOut(EventHandler handler);
    virtual void onMouseOver(EventHandler handler);
    virtual void onDragStart(EventHandler handler);
    virtual void onDragStop(EventHandler handler);
    virtual void onDrag(EventHandler handler);
    virtual void onLeftButtonPress(EventHandler handler);
    virtual void onLeftButtonRelease(EventHandler handler);
    virtual void onLeftButtonClick(EventHandler handler);
    virtual void onRightButtonPress(EventHandler handler);
    virtual void onRightButtonRelease(EventHandler handler);
    virtual void onRightButtonClick(EventHandler handler);
    virtual void onKeyboardPress(EventHandler handler);
    virtual void onKeyboardRelease(EventHandler handler);
};

}
#endif // FALLTERGEIST_INTERACTIVESURFACE_H
