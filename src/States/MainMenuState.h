#ifndef FALLTERGEIST_MAINMENUSTATE_H
#define FALLTERGEIST_MAINMENUSTATE_H

#include "src/Engine/State.h"

namespace Falltergeist
{
class TextArea;

class MainMenuState : public State
{
protected:
    TextArea * _testArea;
public:
    MainMenuState(Game * game);
    virtual ~MainMenuState();
    void init();
    void think();
    void onExitButtonClick();
    void onNewGameButtonClick();
};

}
#endif // FALLTERGEIST_MAINMENUSTATE_H
