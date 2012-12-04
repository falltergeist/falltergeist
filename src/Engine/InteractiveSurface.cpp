#include "src/Engine/InteractiveSurface.h"
#include <iostream>

namespace Falltergeist
{

InteractiveSurface::InteractiveSurface(int width, int height, int x, int y) : Surface(width, height, x, y)
{
    _hovered = false;
    _leftButtonPressed = false;
    _rightButtonPressed = false;
    _onKeyboardPress = 0;
    _onKeyboardRelease = 0;
    _onLeftButtonClick = 0;
    _onLeftButtonPress = 0;
    _onLeftButtonRelease = 0;
    _onMouseIn = 0;
    _onMouseOut = 0;
    _onMouseOver = 0;
    _onRightButtonClick = 0;
    _onRightButtonPress = 0;
    _onRightButtonRelease = 0;
}

InteractiveSurface::InteractiveSurface(Surface * other) : Surface(other)
{
    _hovered = false;
    _leftButtonPressed = false;
    _rightButtonPressed = false;
    _onKeyboardPress = 0;
    _onKeyboardRelease = 0;
    _onLeftButtonClick = 0;
    _onLeftButtonPress = 0;
    _onLeftButtonRelease = 0;
    _onMouseIn = 0;
    _onMouseOut = 0;
    _onMouseOver = 0;
    _onRightButtonClick = 0;
    _onRightButtonPress = 0;
    _onRightButtonRelease = 0;
}

InteractiveSurface::~InteractiveSurface()
{
}

void InteractiveSurface::handle(Event * event, State * state)
{
    event->setSender(this);

    if(event->isMouseEvent())
    {
        // check that the surface under the cursor pointer is not transparent
        int x = event->getX() - getX();
        int y = event->getY() - getY();

        unsigned int alpha = getPixel(x , y) >> 24;
        //std::cout << alpha << std::endl;
        if (alpha > 0)
        {
            switch(event->getSDLEvent()->type)
            {
                case SDL_MOUSEMOTION:
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
                    if (event->getSDLEvent()->button.button == SDL_BUTTON_LEFT)
                    {
                        _leftButtonPressed = true;
                        leftButtonPress(event, state);
                    }
                    else if (event->getSDLEvent()->button.button == SDL_BUTTON_RIGHT)
                    {
                        _rightButtonPressed = true;
                        rightButtonPress(event, state);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event->getSDLEvent()->button.button == SDL_BUTTON_LEFT)
                    {
                        leftButtonRelease(event, state);
                        if (_leftButtonPressed)
                        {
                            leftButtonClick(event, state);
                        }
                        _leftButtonPressed = false;
                    }
                    else if(event->getSDLEvent()->button.button == SDL_BUTTON_RIGHT)
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
            if (event->getSDLEvent()->type == SDL_MOUSEMOTION && _hovered)
            {
                _hovered = false;
                mouseOut(event, state);
            }
            else if(event->getSDLEvent()->type == SDL_MOUSEBUTTONUP)
            {
                if (event->getSDLEvent()->button.button == SDL_BUTTON_LEFT)
                {
                    if (_leftButtonPressed)
                    {
                        leftButtonRelease(event, state);
                        _leftButtonPressed = false;
                    }
                }
                else if(event->getSDLEvent()->button.button == SDL_BUTTON_RIGHT)
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
        if(event->getSDLEvent()->type == SDL_KEYDOWN)
        {
            keyboardPress(event, state);
        }
        else if(event->getSDLEvent()->type == SDL_KEYUP)
        {
            keyboardRelease(event, state);
        }
    }
}

void InteractiveSurface::mouseIn(Event * event, State * state)
{
    needRedraw = true;
    if (_onMouseIn != 0) (state->*_onMouseIn)(event);
}
void InteractiveSurface::mouseOut(Event * event, State * state)
{
    needRedraw = true;
    if (_onMouseOut != 0) (state->*_onMouseOut)(event);
}
void InteractiveSurface::mouseOver(Event * event, State * state)
{
    needRedraw = true;
    if (_onMouseOver != 0) (state->*_onMouseOver)(event);
}
void InteractiveSurface::leftButtonPress(Event * event, State * state)
{
    needRedraw = true;
    if (_onLeftButtonPress != 0) (state->*_onLeftButtonPress)(event);
}
void InteractiveSurface::leftButtonRelease(Event * event, State * state)
{
    needRedraw = true;
    if (_onLeftButtonRelease != 0) (state->*_onLeftButtonRelease)(event);
}
void InteractiveSurface::leftButtonClick(Event * event, State * state)
{
    needRedraw = true;
    if (_onLeftButtonClick != 0) (state->*_onLeftButtonClick)(event);
}
void InteractiveSurface::rightButtonPress(Event * event, State * state)
{
    needRedraw = true;
    if (_onRightButtonPress != 0) (state->*_onRightButtonPress)(event);
}
void InteractiveSurface::rightButtonRelease(Event * event, State * state)
{
    needRedraw = true;
    if (_onRightButtonRelease != 0) (state->*_onRightButtonRelease)(event);
}
void InteractiveSurface::rightButtonClick(Event * event, State * state)
{
    needRedraw = true;
    if (_onRightButtonClick != 0) (state->*_onRightButtonClick)(event);
}
void InteractiveSurface::keyboardPress(Event * event, State * state)
{
    needRedraw = true;
    if (_onKeyboardPress != 0) (state->*_onKeyboardPress)(event);
}
void InteractiveSurface::keyboardRelease(Event * event, State * state)
{
    needRedraw = true;
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


