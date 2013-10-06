#ifndef FALLTERGEIST_PLAYEREDITNAMESTATE_H
#define FALLTERGEIST_PLAYEREDITNAMESTATE_H

#include "../Engine/State.h"
#include "map"

namespace Falltergeist
{
class Game;
class TextArea;

class PlayerEditNameState : public State
{
protected:
    unsigned int _timer;
    TextArea * _name;
    Surface * _cursor;
    std::map<char,char> * _keyCodes;
public:
    PlayerEditNameState(Game * game);
    ~PlayerEditNameState();
    void init();
    void think();
    void onDoneButtonClick(Event * event);
    void onKeyboardPress(Event * event);
};


}


#endif // FALLTERGEIST_PLAYEREDITNAMESTATE_H
