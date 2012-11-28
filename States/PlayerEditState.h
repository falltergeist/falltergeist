#ifndef FALLTERGEIST_PLAYEREDITSTATE_H
#define	FALLTERGEIST_PLAYEREDITSTATE_H

#include "Engine/State.h"
#include "UI/ImageButton.h"
#include "UI/TextArea.h"

namespace Falltergeist
{
class Game;
    
class PlayerEditState : public State
{
protected:
    ImageButton * _increaseStrenghtButton;
    ImageButton * _decreaseStrenghtButton;
    TextArea    * _statsStrenghtLabel;
    ImageButton * _increasePerceptionButton;
    ImageButton * _decreasePerceptionButton;
    TextArea    * _statsPerceptionLabel;
    ImageButton * _increaseEnduranceButton;
    ImageButton * _decreaseEnduranceButton;
    TextArea    * _statsEnduranceLabel;
    ImageButton * _increaseCharismaButton;
    ImageButton * _decreaseCharismaButton;
    TextArea    * _statsCharismaLabel;
    ImageButton * _increaseIntelligenceButton;
    ImageButton * _decreaseIntelligenceButton;
    TextArea    * _statsIntelligenceLabel;
    ImageButton * _increaseAgilityButton;
    ImageButton * _decreaseAgilityButton;
    TextArea    * _statsAgilityLabel;
    ImageButton * _increaseLuckButton;
    ImageButton * _decreaseLuckButton;
    TextArea    * _statsLuckLabel;
public:
    PlayerEditState(Game * game);
    void think();
    virtual ~PlayerEditState();
private:

};

}
#endif	/* FALLTERGEIST_PLAYEREDITSTATE_H */

