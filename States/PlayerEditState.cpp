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
    
    _increaseStrenghtButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38);
    _decreaseStrenghtButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49);
    _statsStrenghtLabel = new TextArea(_t(200,"text/english/game/editor.msg"), 102,46);   
    
    _increasePerceptionButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38 + 33);
    _decreasePerceptionButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49 + 33);
    _statsPerceptionLabel = new TextArea(_t(201,"text/english/game/editor.msg"), 102,46 + 33);   
    
    _increaseEnduranceButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38 + 33*2);
    _decreaseEnduranceButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49 + 33*2);
    _statsEnduranceLabel = new TextArea(_t(202,"text/english/game/editor.msg"), 102,46 + 33*2);   
    
    _increaseCharismaButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38 + 33*3);
    _decreaseCharismaButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49 + 33*3);
    _statsCharismaLabel = new TextArea(_t(203,"text/english/game/editor.msg"), 102,46 + 33*3);   
    
    _increaseIntelligenceButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38 + 33*4);
    _decreaseIntelligenceButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49 + 33*4);
    _statsIntelligenceLabel = new TextArea(_t(204,"text/english/game/editor.msg"), 102,46 + 33*4);   
    
    _increaseAgilityButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38 + 33*5);
    _decreaseAgilityButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49 + 33*5);
    _statsAgilityLabel = new TextArea(_t(205,"text/english/game/editor.msg"), 102,46 + 33*5);   

    _increaseLuckButton = new ImageButton("art/intrface/splsoff.frm","art/intrface/splson.frm",149,38 + 33*6);
    _decreaseLuckButton = new ImageButton("art/intrface/snegoff.frm","art/intrface/snegon.frm",149,49 + 33*6);
    _statsLuckLabel = new TextArea(_t(206,"text/english/game/editor.msg"), 102,46 + 33*6);   
    
    // Traits
    _trait1Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352);
    _trait1Label = new TextArea(_t(100,"text/english/game/trait.msg"), 47, 352);

    _trait2Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13);
    _trait2Label = new TextArea(_t(101,"text/english/game/trait.msg"), 47, 352 + 14);

    _trait3Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13*2 + 1);
    _trait3Label = new TextArea(_t(102,"text/english/game/trait.msg"), 47, 352 + 14*2);

    _trait4Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13*3);
    _trait4Label = new TextArea(_t(103,"text/english/game/trait.msg"), 47, 352 + 14*3 - 1);

    _trait5Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13*4 + 1);
    _trait5Label = new TextArea(_t(104,"text/english/game/trait.msg"), 47, 352 + 14*4 - 1);

    _trait6Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13*5);
    _trait6Label = new TextArea(_t(105,"text/english/game/trait.msg"), 47, 352 + 14*5 - 2);

    _trait7Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13*6 + 1);
    _trait7Label = new TextArea(_t(106,"text/english/game/trait.msg"), 47, 352 + 14*6 - 3);

    _trait8Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",23,352 + 13*7 + 1);
    _trait8Label = new TextArea(_t(107,"text/english/game/trait.msg"), 47, 352 + 14*7 - 3);

    _trait9Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352);
    _trait9Label = new TextArea(_t(108,"text/english/game/trait.msg"), 47, 352);
    _trait9Label->setWidth(244);
    _trait9Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait10Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13);
    _trait10Label = new TextArea(_t(109,"text/english/game/trait.msg"), 47, 352 + 14);
    _trait10Label->setWidth(244);
    _trait10Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait11Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13*2 + 1);
    _trait11Label = new TextArea(_t(110,"text/english/game/trait.msg"), 47, 352 + 14*2);
    _trait11Label->setWidth(244);
    _trait11Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait12Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13*3);
    _trait12Label = new TextArea(_t(111,"text/english/game/trait.msg"), 47, 352 + 14*3 - 1);
    _trait12Label->setWidth(244);
    _trait12Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait13Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13*4 + 1);
    _trait13Label = new TextArea(_t(112,"text/english/game/trait.msg"), 47, 352 + 14*4 - 1);
    _trait13Label->setWidth(244);
    _trait13Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait14Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13*5);
    _trait14Label = new TextArea(_t(113,"text/english/game/trait.msg"), 47, 352 + 14*5 - 2);
    _trait14Label->setWidth(244);
    _trait14Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait15Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13*6 + 1);
    _trait15Label = new TextArea(_t(114,"text/english/game/trait.msg"), 47, 352 + 14*6 - 3);
    _trait15Label->setWidth(244);
    _trait15Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _trait16Button = new ImageButton("art/intrface/tgskloff.frm","art/intrface/tgsklon.frm",299,352 + 13*7 + 1);
    _trait16Label = new TextArea(_t(115,"text/english/game/trait.msg"), 47, 352 + 14*7 - 3);
    _trait16Label->setWidth(244);
    _trait16Label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    add(background);
    // primary stats buttons
    add(_increaseStrenghtButton);
    add(_decreaseStrenghtButton);
    add(_increasePerceptionButton);
    add(_decreasePerceptionButton);
    add(_increaseEnduranceButton);
    add(_decreaseEnduranceButton);
    add(_increaseCharismaButton);
    add(_decreaseCharismaButton);
    add(_increaseIntelligenceButton);
    add(_decreaseIntelligenceButton);
    add(_increaseAgilityButton);
    add(_decreaseAgilityButton);
    add(_increaseLuckButton);
    add(_decreaseLuckButton);
    // primary stats labels
    add(_statsStrenghtLabel);
    add(_statsPerceptionLabel);
    add(_statsEnduranceLabel);
    add(_statsCharismaLabel);
    add(_statsIntelligenceLabel);
    add(_statsAgilityLabel);
    add(_statsLuckLabel);
    // trait buttons
    add(_trait1Button);
    add(_trait2Button);
    add(_trait3Button);
    add(_trait4Button);
    add(_trait5Button);
    add(_trait6Button);
    add(_trait7Button);
    add(_trait8Button);
    add(_trait9Button);
    add(_trait10Button);
    add(_trait11Button);
    add(_trait12Button);
    add(_trait13Button);
    add(_trait14Button);
    add(_trait15Button);
    add(_trait16Button);
    // Trait labels
    add(_trait1Label);
    add(_trait2Label);
    add(_trait3Label);
    add(_trait4Label);
    add(_trait5Label);
    add(_trait6Label);
    add(_trait7Label);
    add(_trait8Label);
    add(_trait9Label);
    add(_trait10Label);
    add(_trait11Label);
    add(_trait12Label);
    add(_trait13Label);
    add(_trait14Label);
    add(_trait15Label);
    add(_trait16Label);

}

PlayerEditState::~PlayerEditState()
{
}

void PlayerEditState::think()
{
    
}

}
