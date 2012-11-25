#include "RightArrowButton.h"
#include "ResourceManager.h"

namespace Falltergeist
{

RightArrowButton::RightArrowButton(int x, int y) : InteractiveSurface(0,0)
{
    loadFromSurface(ResourceManager::getSurface("art/intrface/sru.frm"));
    setX(x);
    setY(y);
}

void RightArrowButton::leftButtonPress(Event *event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/srd.frm"));
    setX(x);
    setY(y);

    //@TODO play button press sound

    if (_onLeftButtonPress != 0) (state->*_onLeftButtonPress)(event);
}

void RightArrowButton::leftButtonRelease(Event * event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/sru.frm"));
    setX(x);
    setY(y);
    if (_onLeftButtonRelease != 0) (state->*_onLeftButtonRelease)(event);
}

void RightArrowButton::mouseIn(Event *event, State *state)
{
    if (_leftButtonPressed)
    {
        int x = getX();
        int y = getY();
        loadFromSurface(ResourceManager::getSurface("art/intrface/srd.frm"));
        setX(x);
        setY(y);
    }
    if (_onMouseIn != 0) (state->*_onMouseIn)(event);
}

void RightArrowButton::mouseOut(Event *event, State *state)
{
    int x = getX();
    int y = getY();
    loadFromSurface(ResourceManager::getSurface("art/intrface/sru.frm"));
    setX(x);
    setY(y);
    if (_onMouseOut != 0) (state->*_onMouseOut)(event);
}


}
