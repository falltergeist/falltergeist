#ifndef FALLTERGEIST_RIGHTARROWBUTTON_H
#define FALLTERGEIST_RIGHTARROWBUTTON_H

#include "InteractiveSurface.h"

namespace Falltergeist
{

class RightArrowButton : public InteractiveSurface
{
public:
    RightArrowButton(int x = 0, int y = 0);
    void leftButtonPress(Event *event, State *state);
    void leftButtonRelease(Event *event, State *state);
    void mouseOut(Event *event, State *state);
    void mouseIn(Event *event, State *state);
};

}
#endif // FALLTERGEIST_RIGHTARROWBUTTON_H
