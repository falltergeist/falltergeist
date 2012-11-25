#ifndef FALLTERGEIST_NEWGAMESTATE_H
#define FALLTERGIEST_NEWGAMESTATE_H

#include "State.h"

namespace Falltergeist
{

class NewGameState : public State
{
public:
    NewGameState(Game * game);
    void init();
    void think();
    void onBackButtonClick(Event * event);
};

}
#endif // FALLTERGEIST_NEWGAMESTATE_H
