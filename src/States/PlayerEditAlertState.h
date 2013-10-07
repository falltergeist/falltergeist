#ifndef FALLTERGEIST_PLAYEREDITALERTSTATE_H
#define FALLTERGEIST_PLAYEREDITALERTSTATE_H

#include "../Engine/State.h"
#include <string>

namespace Falltergeist
{
class Game;

class PlayerEditAlertState : public State
{
protected:
    std::string _message;
public:
    PlayerEditAlertState(Game * game);
    ~PlayerEditAlertState();
    void setMessage(std::string message);
    void init();
    void onDoneButtonClick(Event * event);
};

}

#endif // FALLTERGEIST_PLAYEREDITALERTSTATE_H
