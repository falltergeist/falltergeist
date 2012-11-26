#ifndef FALLTERGEIST_NEWGAMESTATE_H
#define FALLTERGIEST_NEWGAMESTATE_H

#include "State.h"
#include "Surface.h"

namespace Falltergeist
{
class GcdFileType;
class Surface;

class NewGameState : public State
{
protected:
    Surface * _characterImage;
    Surface * _characterImages;
    unsigned char _selectedCharacter;
public:    
    NewGameState(Game * game);
    virtual ~NewGameState();
    void init();
    void think();
    void onBackButtonClick();
    void onPrevCharacterButtonClick();
    void onNextCharacterButtonClick();
};

}
#endif // FALLTERGEIST_NEWGAMESTATE_H
