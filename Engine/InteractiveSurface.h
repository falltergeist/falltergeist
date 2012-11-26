#ifndef FALLTERGEIST_INTERACTIVESURFACE_H
#define FALLTERGEIST_INTERACTIVESURFACE_H

#include "Engine/State.h"
#include "Engine/Surface.h"
#include "Engine/Event.h"

namespace Falltergeist
{

typedef void (State::*EventHandler)(Event*);

class InteractiveSurface : public Surface
{
protected:
    bool _hovered;
    bool _leftButtonPressed;
    bool _rightButtonPressed;
    EventHandler _onMouseIn;
    EventHandler _onMouseOut;
    EventHandler _onMouseOver;
    EventHandler _onLeftButtonPress;
    EventHandler _onLeftButtonRelease;
    EventHandler _onLeftButtonClick;
    EventHandler _onRightButtonRelease;
    EventHandler _onRightButtonPress;
    EventHandler _onRightButtonClick;
    EventHandler _onKeyboardPress;
    EventHandler _onKeyboardRelease;
public:
    InteractiveSurface(int width = 0, int height = 0, int x = 0, int y = 0);
    InteractiveSurface(Surface * other);
    virtual ~InteractiveSurface();
    virtual void handle(Event * event, State *state);
    virtual void mouseIn(Event * event, State * state);
    virtual void mouseOver(Event * event, State * state);
    virtual void mouseOut(Event * event, State * state);
    virtual void leftButtonPress(Event * event, State * state);
    virtual void leftButtonRelease(Event * event, State * state);
    virtual void leftButtonClick(Event * event, State * state);
    virtual void rightButtonPress(Event * event, State * state);
    virtual void rightButtonRelease(Event * event, State * state);
    virtual void rightButtonClick(Event * event, State * state);
    virtual void keyboardPress(Event * event, State * state);
    virtual void keyboardRelease(Event * event, State * state);
    virtual void onMouseIn(EventHandler handler);
    virtual void onMouseOut(EventHandler handler);
    virtual void onMouseOver(EventHandler handler);
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
