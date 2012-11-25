#ifndef FALLTERGEIST_REDSMALLCIRCLEBUTTON_H
#define FALLTERGEIST_REDSMALLCIRCLEBUTTON_H

#include "InteractiveSurface.h"

namespace Falltergeist
{

class RedSmallCircleButton : public InteractiveSurface
{
public:
    RedSmallCircleButton(int x = 0, int y = 0);
    void leftButtonPress(Event *event, State *state);
    void leftButtonRelease(Event *event, State *state);
    void mouseOut(Event *event, State *state);
    void mouseIn(Event *event, State *state);
};

}
#endif // FALLTERGEIST_REDSMALLCIRCLEBUTTON_H
