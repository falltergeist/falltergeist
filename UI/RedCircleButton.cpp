#include "RedCircleButton.h"
#include "ResourceManager.h"

namespace Falltergeist
{

RedCircleButton::RedCircleButton(int x, int y) : InteractiveSurface(0,0)
{  
    loadFromSurface(ResourceManager::getSurface("art/intrface/menuup.frm"));
    setX(x);
    setY(y);
}

void RedCircleButton::leftButtonPress(Event *event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/menudown.frm"));
    setX(x);
    setY(y);

    //@TODO play button press sound

    if (_onLeftButtonPress != 0) (state->*_onLeftButtonPress)(event);
}

void RedCircleButton::leftButtonRelease(Event * event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/menuup.frm"));
    setX(x);
    setY(y);
    if (_onLeftButtonRelease != 0) (state->*_onLeftButtonRelease)(event);
}

void RedCircleButton::mouseIn(Event *event, State *state)
{
    if (_leftButtonPressed)
    {
        int x = getX();
        int y = getY();
        loadFromSurface(ResourceManager::getSurface("art/intrface/menudown.frm"));
        setX(x);
        setY(y);
    }
    if (_onMouseIn != 0) (state->*_onMouseIn)(event);
}

void RedCircleButton::mouseOut(Event *event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/menuup.frm"));
    setX(x);
    setY(y);
    if (_onMouseOut != 0) (state->*_onMouseOut)(event);
}


}
