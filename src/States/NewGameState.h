#ifndef FALLTERGEIST_NEWGAMESTATE_H
#define FALLTERGIEST_NEWGAMESTATE_H

#include "../Engine/State.h"
#include "../Engine/Surface.h"
#include <vector>

namespace Falltergeist
{
class GcdFileType;
class Surface;
class SurfaceSet;
class TextArea;
class Player;

class NewGameState : public State
{
protected:
    SurfaceSet * _characterImages;
    std::vector<Player *> * _characters;
    TextArea * _playerStats1;
    TextArea * _playerStats2;
    TextArea * _playerBio;
    TextArea * _playerName;
    unsigned char _selectedCharacter;
public:    
    NewGameState(Game * game);
    virtual ~NewGameState();
    void changeCharacter();
    void init();
    const char * statToString(unsigned int stat);
    void think();
    void onBackButtonClick();
    void onEditButtonClick();
    void onCreateButtonClick();
    void onPrevCharacterButtonClick();
    void onNextCharacterButtonClick();
};

}
#endif // FALLTERGEIST_NEWGAMESTATE_H
