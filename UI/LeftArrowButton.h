#ifndef FALLTERGEIST_LEFTARROWBUTTON_H
#define FALLTERGEIST_LEFTARROWBUTTON_H

#include "InteractiveSurface.h"

namespace Falltergeist
{

class LeftArrowButton : public InteractiveSurface
{
public:
    LeftArrowButton(int x = 0, int y = 0);
    void leftButtonPress(Event *event, State *state);
    void leftButtonRelease(Event *event, State *state);
    void mouseOut(Event *event, State *state);
    void mouseIn(Event *event, State *state);
};

}
#endif // FALLTERGEIST_LEFTARROWBUTTON_H
