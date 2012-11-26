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
    void onExitButtonClick();
    void onNewGameButtonClick();
};

}
#endif // FALLTERGEIST_MAINMENUSTATE_H
