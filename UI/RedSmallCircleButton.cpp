#include "RedSmallCircleButton.h"
#include "ResourceManager.h"

namespace Falltergeist
{

RedSmallCircleButton::RedSmallCircleButton(int x, int y) : InteractiveSurface(0,0)
{
    loadFromSurface(ResourceManager::getSurface("art/intrface/lilredup.frm"));
    setX(x);
    setY(y);
}

void RedSmallCircleButton::leftButtonPress(Event *event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/lilreddn.frm"));
    setX(x);
    setY(y);

    //@TODO play button press sound

    if (_onLeftButtonPress != 0) (state->*_onLeftButtonPress)(event);
}

void RedSmallCircleButton::leftButtonRelease(Event * event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/lilredup.frm"));
    setX(x);
    setY(y);
    if (_onLeftButtonRelease != 0) (state->*_onLeftButtonRelease)(event);
}

void RedSmallCircleButton::mouseIn(Event *event, State *state)
{
    if (_leftButtonPressed)
    {
        int x = getX();
        int y = getY();
        loadFromSurface(ResourceManager::getSurface("art/intrface/lilreddn.frm"));
        setX(x);
        setY(y);
    }
    if (_onMouseIn != 0) (state->*_onMouseIn)(event);
}

void RedSmallCircleButton::mouseOut(Event *event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/lilredup.frm"));
    setX(x);
    setY(y);
    if (_onMouseOut != 0) (state->*_onMouseOut)(event);
}


}
