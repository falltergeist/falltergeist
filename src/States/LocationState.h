#ifndef FALLTERGEIST_LOCATIONSTATE_H
#define FALLTERGEIST_LOCATIONSTATE_H

#include "../Engine/State.h"

namespace Falltergeist
{
class Game;
class Location;

class LocationState : public State
{
protected:
    Location * _location;
public:
    LocationState(Game * game);
    ~LocationState();
    void init();
};

}

#endif // FALLTERGEIST_LOCATIONSTATE_H
