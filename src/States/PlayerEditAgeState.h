#ifndef FALLTERGEIST_PLAYEREDITAGESTATE_H
#define FALLTERGEIST_PLAYEREDITAGESTATE_H

#include "../Engine/State.h"

namespace Falltergeist
{
class Game;
class BigCounter;

class PlayerEditAgeState : public State
{
protected:
    BigCounter * _counter;
public:
    PlayerEditAgeState(Game * game);
    void init();
    ~PlayerEditAgeState();
    void onIncButtonClick(Event * event);
    void onDecButtonClick(Event * event);
    void onDoneButtonClick(Event * event);
};
}

#endif // FALLTERGEIST_PLAYEREDITAGESTATE_H
