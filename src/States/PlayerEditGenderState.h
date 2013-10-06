#ifndef FALLTERGEIST_PLAYEREDITGENDERSTATE_H
#define FALLTERGEIST_PLAYEREDITGENDERSTATE_H

#include "../Engine/State.h"

namespace Falltergeist
{
class Game;
class SurfaceSet;

class PlayerEditGenderState : public State
{
protected:
    SurfaceSet * _maleImage;
    SurfaceSet * _femaleImage;
public:
    PlayerEditGenderState(Game * game);
    void init();
    void onFemaleButtonPress(Event * event);
    void onMaleButtonPress(Event * event);
    void onDoneButtonClick(Event * event);
};

}

#endif // FALLTERGEIST_PLAYEREDITGENDERSTATE_H
