#ifndef FALLTERGEIST_REDCIRCLEBUTTON_H
#define FALLTERGEIST_REDCIRCLEBUTTON_H

#include "InteractiveSurface.h"

namespace Falltergeist
{

class RedCircleButton : public InteractiveSurface
{
public:
    RedCircleButton(int x = 0, int y = 0);
    void leftButtonPress(Event *event, State *state);
    void leftButtonRelease(Event *event, State *state);
    void mouseOut(Event *event, State *state);
    void mouseIn(Event *event, State *state);
};

}
#endif // FALLTERGEIST_REDCIRCLEBUTTON_H
