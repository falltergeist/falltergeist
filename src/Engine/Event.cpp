#include "src/Engine/Event.h"

namespace Falltergeist
{

Event::Event(SDL_Event * event) : _event(event)
{
    _isMouseEvent = false;
    _isKeyboardEvent = false;
    _x = -1;
    _y = -1;
    _keyCode = -1;

    switch(_event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            _isMouseEvent = true;
            _x = event->button.x;
            _y = event->button.y;
            break;
        case SDL_MOUSEMOTION:
            _isMouseEvent = true;
            _x = event->motion.x;
            _y = event->motion.y;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            _isKeyboardEvent = true;
            _keyCode = event->key.keysym.scancode;
            break;
    }
}

Event::~Event()
{
}

SDL_Event * Event::getSDLEvent()
{
    return _event;
}

InteractiveSurface * Event::getSender()
{
    return _sender;
}

void Event::setSender(InteractiveSurface * sender)
{
    _sender = sender;
}

bool Event::isMouseEvent()
{
    return _isMouseEvent;
}

bool Event::isKeyboardEvent()
{
    return _isKeyboardEvent;
}

int Event::getX()
{
    return _x;
}

int Event::getY()
{
    return _y;
}

int Event::getKeyCode()
{
    return _keyCode;
}

}
