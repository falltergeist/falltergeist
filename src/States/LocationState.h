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
    Surface * _elevation;
    Surface * _camera;
    unsigned int _direction;
    unsigned int _cameraX;
    unsigned int _cameraY;
    unsigned int _lastTicks;
public:
    LocationState(Game * game);
    ~LocationState();
    void init();
    void think();
};

}

#endif // FALLTERGEIST_LOCATIONSTATE_H
