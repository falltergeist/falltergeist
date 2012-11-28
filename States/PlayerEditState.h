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
    // Traits
    ImageButton * _trait1Button;
    TextArea * _trait1Label;
    ImageButton * _trait2Button;
    TextArea * _trait2Label;
    ImageButton * _trait3Button;
    TextArea * _trait3Label;
    ImageButton * _trait4Button;
    TextArea * _trait4Label;
    ImageButton * _trait5Button;
    TextArea * _trait5Label;
    ImageButton * _trait6Button;
    TextArea * _trait6Label;
    ImageButton * _trait7Button;
    TextArea * _trait7Label;
    ImageButton * _trait8Button;
    TextArea * _trait8Label;
    ImageButton * _trait9Button;
    TextArea * _trait9Label;
    ImageButton * _trait10Button;
    TextArea * _trait10Label;
    ImageButton * _trait11Button;
    TextArea * _trait11Label;
    ImageButton * _trait12Button;
    TextArea * _trait12Label;
    ImageButton * _trait13Button;
    TextArea * _trait13Label;
    ImageButton * _trait14Button;
    TextArea * _trait14Label;
    ImageButton * _trait15Button;
    TextArea * _trait15Label;
    ImageButton * _trait16Button;
    TextArea * _trait16Label;

public:
    PlayerEditState(Game * game);
    void think();
    virtual ~PlayerEditState();
private:

};

}
#endif	/* FALLTERGEIST_PLAYEREDITSTATE_H */

