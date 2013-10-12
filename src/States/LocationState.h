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
    Surface * _background;
    unsigned int _direction;
    unsigned int _cameraX;
    unsigned int _cameraY;
    unsigned int _scrollTicks;
public:
    LocationState(Game * game);
    ~LocationState();
    virtual void init();
    virtual void think();
    virtual void blit();
};

}

#endif // FALLTERGEIST_LOCATIONSTATE_H
