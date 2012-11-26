#ifndef FALLTERGEIST_STARTSTATE_H
#define FALLTERGEIST_STARTSTATE_H

#include "State.h"

namespace Falltergeist
{

class StartState : public State
{
public:
    StartState(Game * game);
    virtual ~StartState();
    void think();
};

}
#endif // FALLTERGEIST_STARTSTATE_H

