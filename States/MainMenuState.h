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
    void onButton1Click();
    void onButton1Press();
    void onButton1Release();
    void onButton2Press();
};

}
#endif // FALLTERGEIST_MAINMENUSTATE_H
