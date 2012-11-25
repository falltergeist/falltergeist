#ifndef FALLTERGEIST_MAINMENUSTATE_H
#define FALLTERGEIST_MAINMENUSTATE_H

#include "State.h"

namespace Falltergeist
{

class MainMenuState : public State
{
public:
    MainMenuState(Game * game);
    void init();
    void think();
    void onExitButtonClick(Event * event);
    void onNewGameButtonClick(Event * event);
};

}
#endif // FALLTERGEIST_MAINMENUSTATE_H
