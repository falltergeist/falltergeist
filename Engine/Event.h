#ifndef FALLTERGEIST_EVENT_H
#define FALLTERGEIST_EVENT_H

#include <SDL/SDL.h>

namespace Falltergeist
{

class InteractiveSurface;

class Event
{
protected:
    SDL_Event * _event;
    InteractiveSurface * _sender;
    int _x;
    int _y;
    int _keyCode;
    bool _isMouseEvent;
    bool _isKeyboardEvent;
public:
    Event(SDL_Event * event);
    virtual ~Event();
    void setSender(InteractiveSurface * sender);
    InteractiveSurface * getSender();
    int getX();
    int getY();
    int getKeyCode();
    SDL_Event * getSDLEvent();
    bool isMouseEvent();
    bool isKeyboardEvent();
};

}
#endif // FALLTERGEIST_EVENT_H
