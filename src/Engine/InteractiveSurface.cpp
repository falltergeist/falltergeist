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

// C++ standard includes

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

InteractiveSurface::InteractiveSurface(libfalltergeist::FrmFileType* frm, unsigned int direction, unsigned int frame) : Surface(frm, direction, frame)
{
}

InteractiveSurface::InteractiveSurface(int width, int height, int x, int y) : Surface(width, height, x, y)
{
}

InteractiveSurface::InteractiveSurface(Surface* other) : Surface(other)
{
}

InteractiveSurface::~InteractiveSurface()
{
}

void InteractiveSurface::handle(Event* event, State* state)
{
    event->setSender(this);

    if(event->isMouseEvent())
    {
        // check that the surface under the cursor pointer is not transparent
        int x = event->x() - this->x() - this->xOffset();
        int y = event->y() - this->y() - this->yOffset();

        unsigned int alpha = pixel(x , y) >> 24;
        if (alpha > 0)
        {
            switch(event->SDLEvent()->type)
            {
                case SDL_MOUSEMOTION:
                    if (_leftButtonPressed)
                    {
                        if (!_drag)
                        {
                            _drag = true;
                            dragStart(event, state);
                        }
                        else
                        {
                            drag(event, state);
                        }
                    }
                    if (!_hovered)
                    {
                        _hovered = true;
                        mouseIn(event, state);
                    }
                    else
                    {
                        mouseOver(event, state);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event->SDLEvent()->button.button == SDL_BUTTON_LEFT)
                    {
                        _leftButtonPressed = true;
                        leftButtonPress(event, state);
                    }
                    else if (event->SDLEvent()->button.button == SDL_BUTTON_RIGHT)
                    {
                        _rightButtonPressed = true;
                        rightButtonPress(event, state);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:                
                    if (event->SDLEvent()->button.button == SDL_BUTTON_LEFT)
                    {
                        leftButtonRelease(event, state);
                        if (_leftButtonPressed)
                        {
                            if (_drag)
                            {
                                _drag = false;
                                dragStop(event, state);
                            }
                            leftButtonClick(event, state);
                        }
                        _leftButtonPressed = false;
                    }
                    else if(event->SDLEvent()->button.button == SDL_BUTTON_RIGHT)
                    {
                        rightButtonRelease(event, state);
                        if (_rightButtonPressed)
                        {
                            rightButtonClick(event, state);
                        }
                        _rightButtonPressed = false;
                    }
                    break;
            }
        }
        else
        {
            if (event->SDLEvent()->type == SDL_MOUSEMOTION && _hovered)
            {
                if (_drag)
                {
                    drag(event, state);
                }
                _hovered = false;
                mouseOut(event, state);

            }
            else if (event->SDLEvent()->type == SDL_MOUSEMOTION && !_hovered)
            {
                if (_drag)
                {
                    drag(event, state);
                }
            }
            else if(event->SDLEvent()->type == SDL_MOUSEBUTTONUP)
            {
                if (event->SDLEvent()->button.button == SDL_BUTTON_LEFT)
                {
                    if (_leftButtonPressed)
                    {
                        if (_drag)
                        {
                            _drag = false;
                            dragStop(event, state);
                        }
                        leftButtonRelease(event, state);
                        _leftButtonPressed = false;
                    }
                }
                else if(event->SDLEvent()->button.button == SDL_BUTTON_RIGHT)
                {
                    if (_rightButtonPressed)
                    {
                        rightButtonRelease(event, state);
                        _rightButtonPressed = false;
                    }
                }
            }
        }
    }
    else if(event->isKeyboardEvent())
    {
        if(event->SDLEvent()->type == SDL_KEYDOWN)
        {
            keyboardPress(event, state);
        }
        else if(event->SDLEvent()->type == SDL_KEYUP)
        {
            keyboardRelease(event, state);
        }
    }
}

void InteractiveSurface::mouseIn(Event* event, State* state)
{
    if (_onMouseIn != 0) (state->*_onMouseIn)(event);
}
void InteractiveSurface::mouseOut(Event* event, State* state)
{
    if (_onMouseOut != 0) (state->*_onMouseOut)(event);
}
void InteractiveSurface::mouseOver(Event* event, State* state)
{
    if (_onMouseOver != 0) (state->*_onMouseOver)(event);
}
void InteractiveSurface::dragStart(Event* event, State* state)
{
    if (_onDragStart != 0) (state->*_onDragStart)(event);
}
void InteractiveSurface::dragStop(Event* event, State* state)
{
    if (_onDragStop != 0) (state->*_onDragStop)(event);
}
void InteractiveSurface::drag(Event* event, State* state)
{
    if (_onDrag != 0) (state->*_onDrag)(event);
}
void InteractiveSurface::leftButtonPress(Event* event, State* state)
{
    if (_onLeftButtonPress != 0) (state->*_onLeftButtonPress)(event);
}
void InteractiveSurface::leftButtonRelease(Event* event, State* state)
{
    if (_onLeftButtonRelease != 0) (state->*_onLeftButtonRelease)(event);
}
void InteractiveSurface::leftButtonClick(Event* event, State* state)
{
    if (_onLeftButtonClick != 0) (state->*_onLeftButtonClick)(event);
}
void InteractiveSurface::rightButtonPress(Event* event, State* state)
{
    if (_onRightButtonPress != 0) (state->*_onRightButtonPress)(event);
}
void InteractiveSurface::rightButtonRelease(Event* event, State* state)
{
    if (_onRightButtonRelease != 0) (state->*_onRightButtonRelease)(event);
}
void InteractiveSurface::rightButtonClick(Event* event, State* state)
{
    if (_onRightButtonClick != 0) (state->*_onRightButtonClick)(event);
}
void InteractiveSurface::keyboardPress(Event* event, State* state)
{
    if (_onKeyboardPress != 0) (state->*_onKeyboardPress)(event);
}
void InteractiveSurface::keyboardRelease(Event* event, State* state)
{
    if (_onKeyboardRelease != 0) (state->*_onKeyboardRelease)(event);
}

void InteractiveSurface::onMouseIn(EventHandler handler)
{
    _onMouseIn = handler;
}

void InteractiveSurface::onMouseOut(EventHandler handler)
{
    _onMouseOut = handler;
}

void InteractiveSurface::onMouseOver(EventHandler handler)
{
    _onMouseOver = handler;
}

void InteractiveSurface::onDragStart(EventHandler handler)
{
    _onDragStart = handler;
}

void InteractiveSurface::onDragStop(EventHandler handler)
{
    _onDragStop = handler;
}

void InteractiveSurface::onDrag(EventHandler handler)
{
    _onDrag = handler;
}

void InteractiveSurface::onLeftButtonClick(EventHandler handler)
{
    _onLeftButtonClick = handler;
}

void InteractiveSurface::onLeftButtonPress(EventHandler handler)
{
    _onLeftButtonPress = handler;
}

void InteractiveSurface::onLeftButtonRelease(EventHandler handler)
{
    _onLeftButtonRelease = handler;
}

void InteractiveSurface::onRightButtonClick(EventHandler handler)
{
    _onRightButtonClick = handler;
}

void InteractiveSurface::onRightButtonPress(EventHandler handler)
{
    _onRightButtonPress = handler;
}

void InteractiveSurface::onRightButtonRelease(EventHandler handler)
{
    _onRightButtonRelease = handler;
}

void InteractiveSurface::onKeyboardPress(EventHandler handler)
{
    _onKeyboardPress = handler;
}

void InteractiveSurface::onKeyboardRelease(EventHandler handler)
{
    _onKeyboardRelease = handler;
}

}


