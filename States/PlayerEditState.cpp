#include "PlayerEditState.h"
#include "Engine/Game.h"
#include "Engine/Player.h"
#include "Engine/ResourceManager.h"
#include "UI/ImageButton.h"
#include "Engine/Surface.h"
#include "UI/BigCounter.h"
#include "UI/ClickMask.h"

namespace Falltergeist
{

PlayerEditState::PlayerEditState(Game * game) : State(game)
{
    Surface * background = ResourceManager::getSurface("art/intrface/edtrcrte.frm"); 
    
    _increaseStrengthButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 38);
    _increaseStrengthButton->onLeftButtonClick((EventHandler)&PlayerEditState::onIncreaseStrengthButtonClick);
    _decreaseStrengthButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 49);
    _decreaseStrengthButton->onLeftButtonClick((EventHandler)&PlayerEditState::onDecreaseStrengthButtonClick);
    _statsStrengthLabel = new TextArea(102, 46);
    _statsStrengthCounter = new BigCounter(59, 37);
    ClickMask * statsStrenghtClickMask = new ClickMask(133, 26, 14, 36);
    statsStrenghtClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onStrengthSelected);

    _increasePerceptionButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 38 + 33);
    _increasePerceptionButton->onLeftButtonClick((EventHandler) &PlayerEditState::onIncreasePerceptionButtonClick);
    _decreasePerceptionButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 49 + 33);
    _decreasePerceptionButton->onLeftButtonClick((EventHandler) &PlayerEditState::onDecreasePerceptionButtonClick);
    _statsPerceptionLabel = new TextArea(102, 79);
    _statsPerceptionCounter = new BigCounter(59, 37 + 33);
    ClickMask * statsPerceptionClickMask = new ClickMask(133, 26, 14, 36 + 33);
    statsPerceptionClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onPerceptionSelected);

    _increaseEnduranceButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 38 + 33*2);
    _increaseEnduranceButton->onLeftButtonClick((EventHandler) &PlayerEditState::onIncreaseEnduranceButtonClick);
    _decreaseEnduranceButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 49 + 33*2);
    _decreaseEnduranceButton->onLeftButtonClick((EventHandler) &PlayerEditState::onDecreaseEnduranceButtonClick);
    _statsEnduranceLabel = new TextArea(102, 112);
    _statsEnduranceCounter = new BigCounter(59, 37 + 33*2);
    ClickMask * statsEnduranceClickMask = new ClickMask(133, 26, 14, 36 + 33*2);
    statsEnduranceClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onEnduranceSelected);

    _increaseCharismaButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 38 + 33*3);
    _increaseCharismaButton->onLeftButtonClick((EventHandler) &PlayerEditState::onIncreaseCharismaButtonClick);
    _decreaseCharismaButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 49 + 33*3);
    _decreaseCharismaButton->onLeftButtonClick((EventHandler) &PlayerEditState::onDecreaseCharismaButtonClick);
    _statsCharismaLabel = new TextArea(102, 145);
    _statsCharismaCounter = new BigCounter(59, 37 + 33*3);
    ClickMask * statsCharismaClickMask = new ClickMask(133, 26, 14, 36 + 33*3);
    statsCharismaClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onCharismaSelected);

    _increaseIntelligenceButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 38 + 33*4);
    _increaseIntelligenceButton->onLeftButtonClick((EventHandler) &PlayerEditState::onIncreaseIntelligenceButtonClick);
    _decreaseIntelligenceButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 49 + 33*4);
    _decreaseIntelligenceButton->onLeftButtonClick((EventHandler) &PlayerEditState::onDecreaseIntelligenceButtonClick);
    _statsIntelligenceLabel = new TextArea(102, 178);
    _statsIntelligenceCounter = new BigCounter(59, 37 + 33*4);
    ClickMask * statsIntelligenceClickMask = new ClickMask(133, 26, 14, 36 + 33*4);
    statsIntelligenceClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onIntelligenceSelected);

    _increaseAgilityButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 38 + 33*5);
    _increaseAgilityButton->onLeftButtonClick((EventHandler) &PlayerEditState::onIncreaseAgilityButtonClick);
    _decreaseAgilityButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 49 + 33*5);
    _decreaseAgilityButton->onLeftButtonClick((EventHandler) &PlayerEditState::onDecreaseAgilityButtonClick);
    _statsAgilityLabel = new TextArea(102, 211);
    _statsAgilityCounter = new BigCounter(59, 37 + 33*5);
    ClickMask * statsAgilityClickMask = new ClickMask(133, 26, 14, 36 + 33*5);
    statsAgilityClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onAgilitySelected);

    _increaseLuckButton = new ImageButton("art/intrface/splsoff.frm", "art/intrface/splson.frm", 149, 236);
    _increaseLuckButton->onLeftButtonClick((EventHandler) &PlayerEditState::onIncreaseLuckButtonClick);
    _decreaseLuckButton = new ImageButton("art/intrface/snegoff.frm", "art/intrface/snegon.frm", 149, 247);
    _decreaseLuckButton->onLeftButtonClick((EventHandler) &PlayerEditState::onDecreaseLuckButtonClick);
    _statsLuckLabel = new TextArea(102, 244);
    _statsLuckCounter = new BigCounter(59, 37 + 33*6);
    ClickMask * statsLuckClickMask = new ClickMask(133, 26, 14, 36 + 33*6);
    statsLuckClickMask->onLeftButtonClick((EventHandler) &PlayerEditState::onLuckSelected);

    _statsFreeCounter = new BigCounter(126,282);

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
    add(_increaseStrengthButton);
    add(_decreaseStrengthButton);
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
    add(_statsStrengthLabel);
    add(_statsPerceptionLabel);
    add(_statsEnduranceLabel);
    add(_statsCharismaLabel);
    add(_statsIntelligenceLabel);
    add(_statsAgilityLabel);
    add(_statsLuckLabel);
    // primary stats counters
    add(_statsStrengthCounter);
    add(_statsPerceptionCounter);
    add(_statsEnduranceCounter);
    add(_statsCharismaCounter);
    add(_statsIntelligenceCounter);
    add(_statsAgilityCounter);
    add(_statsLuckCounter);

    add(_statsFreeCounter);

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

    add(statsStrenghtClickMask);
    add(statsPerceptionClickMask);
    add(statsEnduranceClickMask);
    add(statsCharismaClickMask);
    add(statsIntelligenceClickMask);
    add(statsAgilityClickMask);
    add(statsLuckClickMask);

}

PlayerEditState::~PlayerEditState()
{
}

void PlayerEditState::think()
{
    _statsStrengthLabel->setText(_t(199 + _game->getPlayer()->strength, "text/english/game/editor.msg"));
    _statsStrengthCounter->setNumber(_game->getPlayer()->strength);

    _statsPerceptionLabel->setText(_t(199 + _game->getPlayer()->perception, "text/english/game/editor.msg"));
    _statsPerceptionCounter->setNumber(_game->getPlayer()->perception);

    _statsEnduranceLabel->setText(_t(199 + _game->getPlayer()->endurance, "text/english/game/editor.msg"));
    _statsEnduranceCounter->setNumber(_game->getPlayer()->endurance);

    _statsCharismaLabel->setText(_t(199 + _game->getPlayer()->charisma, "text/english/game/editor.msg"));
    _statsCharismaCounter->setNumber(_game->getPlayer()->charisma);

    _statsIntelligenceLabel->setText(_t(199 + _game->getPlayer()->intelligence, "text/english/game/editor.msg"));
    _statsIntelligenceCounter->setNumber(_game->getPlayer()->intelligence);

    _statsAgilityLabel->setText(_t(199 + _game->getPlayer()->agility, "text/english/game/editor.msg"));
    _statsAgilityCounter->setNumber(_game->getPlayer()->agility);

    _statsLuckLabel->setText(_t(199 + _game->getPlayer()->luck, "text/english/game/editor.msg"));
    _statsLuckCounter->setNumber(_game->getPlayer()->luck);

    _statsFreeCounter->setNumber(_game->getPlayer()->freeStatsPoints);

}

void PlayerEditState::onIncreaseStrengthButtonClick()
{
    onStrengthSelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->strength < 10)
    {
        _game->getPlayer()->strength++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseStrengthButtonClick()
{
    onStrengthSelected();
    if (_game->getPlayer()->strength > 2)
    {
        _game->getPlayer()->strength--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreasePerceptionButtonClick()
{
    onPerceptionSelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->perception < 10)
    {
        _game->getPlayer()->perception++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreasePerceptionButtonClick()
{
    onPerceptionSelected();
    if (_game->getPlayer()->perception > 2)
    {
        _game->getPlayer()->perception--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseEnduranceButtonClick()
{
    onEnduranceSelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->endurance < 10)
    {
        _game->getPlayer()->endurance++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseEnduranceButtonClick()
{
    onEnduranceSelected();
    if (_game->getPlayer()->endurance > 2)
    {
        _game->getPlayer()->endurance--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseCharismaButtonClick()
{
    onCharismaSelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->charisma < 10)
    {
        _game->getPlayer()->charisma++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseCharismaButtonClick()
{
    onCharismaSelected();
    if (_game->getPlayer()->charisma > 2)
    {
        _game->getPlayer()->charisma--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseIntelligenceButtonClick()
{
    onIntelligenceSelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->intelligence < 10)
    {
        _game->getPlayer()->intelligence++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseIntelligenceButtonClick()
{
    onIntelligenceSelected();
    if (_game->getPlayer()->intelligence > 2)
    {
        _game->getPlayer()->intelligence--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseAgilityButtonClick()
{
    onAgilitySelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->agility < 10)
    {
        _game->getPlayer()->agility++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseAgilityButtonClick()
{
    onAgilitySelected();
    if (_game->getPlayer()->agility > 2)
    {
        _game->getPlayer()->agility--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseLuckButtonClick()
{
    onLuckSelected();
    if (_game->getPlayer()->freeStatsPoints == 0) return;
    if (_game->getPlayer()->luck < 10)
    {
        _game->getPlayer()->luck++;
        _game->getPlayer()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseLuckButtonClick()
{
    onLuckSelected();
    if (_game->getPlayer()->luck > 2)
    {
        _game->getPlayer()->luck--;
        _game->getPlayer()->freeStatsPoints++;
    }
}

void PlayerEditState::onStrengthSelected()
{
    std::cout << "Strength" << std::endl;
}

void PlayerEditState::onPerceptionSelected()
{
    std::cout << "Perception" << std::endl;
}

void PlayerEditState::onEnduranceSelected()
{
    std::cout << "Endurance" << std::endl;
}

void PlayerEditState::onCharismaSelected()
{
    std::cout << "Charisma" << std::endl;
}

void PlayerEditState::onIntelligenceSelected()
{
    std::cout << "Intelligence" << std::endl;
}

void PlayerEditState::onAgilitySelected()
{
    std::cout << "Agility" << std::endl;
}

void PlayerEditState::onLuckSelected()
{
    std::cout << "Luck" << std::endl;
}

}
