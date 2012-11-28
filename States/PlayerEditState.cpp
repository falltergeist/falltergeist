#include "PlayerEditState.h"
#include "Engine/Game.h"
#include "Engine/ResourceManager.h"
#include "UI/ImageButton.h"
#include "Engine/Surface.h"

namespace Falltergeist
{

PlayerEditState::PlayerEditState(Game * game) : State(game)
{
    Surface * background = ResourceManager::getSurface("art/intrface/edtrcrte.frm"); 
    
    _increaseStrenghtButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39);
    _decreaseStrenghtButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50);
    _statsStrenghtLabel = new TextArea(_t(200,"text/english/game/editor.msg"), 102,46);   
    
    _increasePerceptionButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39 + 33);
    _decreasePerceptionButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50 + 33);
    _statsPerceptionLabel = new TextArea(_t(201,"text/english/game/editor.msg"), 102,46 + 33);   
    
    _increaseEnduranceButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39 + 33*2);
    _decreaseEnduranceButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50 + 33*2);
    _statsEnduranceLabel = new TextArea(_t(202,"text/english/game/editor.msg"), 102,46 + 33*2);   
    
    _increaseCharismaButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39 + 33*3);
    _decreaseCharismaButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50 + 33*3);
    _statsCharismaLabel = new TextArea(_t(203,"text/english/game/editor.msg"), 102,46 + 33*3);   
    
    _increaseIntelligenceButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39 + 33*4);
    _decreaseIntelligenceButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50 + 33*4);
    _statsIntelligenceLabel = new TextArea(_t(204,"text/english/game/editor.msg"), 102,46 + 33*4);   
    
    _increaseAgilityButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39 + 33*5);
    _decreaseAgilityButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50 + 33*5);
    _statsAgilityLabel = new TextArea(_t(205,"text/english/game/editor.msg"), 102,46 + 33*5);   

    _increaseLuckButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,39 + 33*6);
    _decreaseLuckButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,50 + 33*6);
    _statsLuckLabel = new TextArea(_t(206,"text/english/game/editor.msg"), 102,46 + 33*6);   
    
    add(background);
    add(_increaseStrenghtButton);
    add(_decreaseStrenghtButton);
    add(_statsStrenghtLabel);
    add(_increasePerceptionButton);
    add(_decreasePerceptionButton);
    add(_statsPerceptionLabel);
    add(_increaseEnduranceButton);
    add(_decreaseEnduranceButton);
    add(_statsEnduranceLabel);
    add(_increaseCharismaButton);
    add(_decreaseCharismaButton);
    add(_statsCharismaLabel);
    add(_increaseIntelligenceButton);
    add(_decreaseIntelligenceButton);
    add(_statsIntelligenceLabel);
    add(_increaseAgilityButton);
    add(_decreaseAgilityButton);
    add(_statsAgilityLabel);
    add(_increaseLuckButton);
    add(_decreaseLuckButton);
    add(_statsLuckLabel);
}

PlayerEditState::~PlayerEditState()
{
}

void PlayerEditState::think()
{
    
}

}
