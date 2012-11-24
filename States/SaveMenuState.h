#ifndef SAVEMENUSTATE_H
#define SAVEMENUSTATE_H

#include "Game.h"
#include "State.h"

namespace Falltergeist
{

class SaveMenuState : public State
{
public:
    SaveMenuState(Game * game);
    void onButton2Click();
    void think();
    void init();
};

}
#endif // SAVEMENUSTATE_H
