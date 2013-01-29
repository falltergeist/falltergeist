/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../States/PlayerEditState.h"
#include "../Engine/Game.h"
#include "../Engine/Player.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{

PlayerEditState::PlayerEditState(Game * game) : State(game)
{
    _checkedLabels = new std::vector<TextArea *>;
    _labels = new std::map<std::string, TextArea *>;
    _counters = new std::map<std::string, BigCounter *>;
    _buttons = new std::map<std::string, ImageButton *>;
    _masks= new std::map<std::string, HiddenMask *>;

    _background = _game->resourceManager()->surface("art/intrface/edtrcrte.frm");
    
    // Primary stats buttons
    {
        const char * plusOn   = "art/intrface/splson.frm";
        const char * plusOff  = "art/intrface/splsoff.frm";
        const char * minusOn  = "art/intrface/snegon.frm";
        const char * minusOff = "art/intrface/snegoff.frm";

        _addButton("stats_strength_increase",     new ImageButton(plusOff,  plusOn,  149, 38));
        _addButton("stats_strength_decrease",     new ImageButton(minusOff, minusOn, 149, 49));
        _addButton("stats_perception_increase",   new ImageButton(plusOff,  plusOn,  149, 71));
        _addButton("stats_perception_decrease",   new ImageButton(minusOff, minusOn, 149, 82));
        _addButton("stats_endurance_increase",    new ImageButton(plusOff,  plusOn,  149, 104));
        _addButton("stats_endurance_decrease",    new ImageButton(minusOff, minusOn, 149, 115));
        _addButton("stats_charisma_increase",     new ImageButton(plusOff,  plusOn,  149, 137));
        _addButton("stats_charisma_decrease",     new ImageButton(minusOff, minusOn, 149, 148));
        _addButton("stats_intelligence_increase", new ImageButton(plusOff,  plusOn,  149, 170));
        _addButton("stats_intelligence_decrease", new ImageButton(minusOff, minusOn, 149, 181));
        _addButton("stats_agility_increase",      new ImageButton(plusOff,  plusOn,  149, 203));
        _addButton("stats_agility_decrease",      new ImageButton(minusOff, minusOn, 149, 214));
        _addButton("stats_luck_increase",         new ImageButton(plusOff,  plusOn,  149, 236));
        _addButton("stats_luck_decrease",         new ImageButton(minusOff, minusOn, 149, 247));
    }
    // Primary stats labels
    {
        _addLabel("stats_strength",     new TextArea(102, 46));
        _addLabel("stats_perception",   new TextArea(102, 79));
        _addLabel("stats_endurance",    new TextArea(102, 112));
        _addLabel("stats_charisma",     new TextArea(102, 145));
        _addLabel("stats_intelligence", new TextArea(102, 178));
        _addLabel("stats_agility",      new TextArea(102, 211));
        _addLabel("stats_luck",         new TextArea(102, 244));
    }
    // Primary stats counters
    {
        _addCounter("stats_strength",     new BigCounter(59, 37));
        _addCounter("stats_perception",   new BigCounter(59, 70));
        _addCounter("stats_endurance",    new BigCounter(59, 103));
        _addCounter("stats_charisma",     new BigCounter(59, 136));
        _addCounter("stats_intelligence", new BigCounter(59, 169));
        _addCounter("stats_agility",      new BigCounter(59, 202));
        _addCounter("stats_luck",         new BigCounter(59, 235));
        // Free stats points counter
        _addCounter("stats_points",       new BigCounter(126, 282));
    }


    // Primaty stats hidden masks
    {
        _addMask("stats_strength",     new HiddenMask(133, 29, 14, 36));
        _addMask("stats_perception",   new HiddenMask(133, 29, 14, 36 + 33));
        _addMask("stats_endurance",    new HiddenMask(133, 29, 14, 36 + 33*2));
        _addMask("stats_charisma",     new HiddenMask(133, 29, 14, 36 + 33*3));
        _addMask("stats_intelligence", new HiddenMask(133, 29, 14, 36 + 33*4));
        _addMask("stats_agility",      new HiddenMask(133, 29, 14, 36 + 33*5));
        _addMask("stats_luck",         new HiddenMask(133, 29, 14, 36 + 33*6));
    }

    // Traits labels
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/trait.msg");
        _addLabel("traits_1",  new TextArea(msg->message(100), 47, 352));
        _addLabel("traits_2",  new TextArea(msg->message(101), 47, 366));
        _addLabel("traits_3",  new TextArea(msg->message(102), 47, 380));
        _addLabel("traits_4",  new TextArea(msg->message(103), 47, 393));
        _addLabel("traits_5",  new TextArea(msg->message(104), 47, 407));
        _addLabel("traits_6",  new TextArea(msg->message(105), 47, 420));
        _addLabel("traits_7",  new TextArea(msg->message(106), 47, 433));
        _addLabel("traits_8",  new TextArea(msg->message(107), 47, 447));
        _addLabel("traits_9",  new TextArea(msg->message(108), 47, 352))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_10", new TextArea(msg->message(109), 47, 366))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_11", new TextArea(msg->message(110), 47, 380))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_12", new TextArea(msg->message(111), 47, 393))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_13", new TextArea(msg->message(112), 47, 407))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_14", new TextArea(msg->message(113), 47, 420))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_15", new TextArea(msg->message(114), 47, 433))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_16", new TextArea(msg->message(115), 47, 447))->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    }
    // Traits buttons
    {
        const char * on  = "art/intrface/tgsklon.frm";
        const char * off = "art/intrface/tgskloff.frm";
        _addButton("traits_1",  new ImageButton(off, on, 23,  352));
        _addButton("traits_2",  new ImageButton(off, on, 23,  365));
        _addButton("traits_3",  new ImageButton(off, on, 23,  379));
        _addButton("traits_4",  new ImageButton(off, on, 23,  391));
        _addButton("traits_5",  new ImageButton(off, on, 23,  405));
        _addButton("traits_6",  new ImageButton(off, on, 23,  417));
        _addButton("traits_7",  new ImageButton(off, on, 23,  431));
        _addButton("traits_8",  new ImageButton(off, on, 23,  444));
        _addButton("traits_9",  new ImageButton(off, on, 299, 352));
        _addButton("traits_10", new ImageButton(off, on, 299, 365));
        _addButton("traits_11", new ImageButton(off, on, 299, 379));
        _addButton("traits_12", new ImageButton(off, on, 299, 391));
        _addButton("traits_13", new ImageButton(off, on, 299, 405));
        _addButton("traits_14", new ImageButton(off, on, 299, 417));
        _addButton("traits_15", new ImageButton(off, on, 299, 431));
        _addButton("traits_16", new ImageButton(off, on, 299, 444));
    }

    // Event handlers
    _buttons->at("stats_strength_increase")->onLeftButtonClick(     (EventHandler) &PlayerEditState::onIncreaseStrengthButtonClick);
    _buttons->at("stats_strength_decrease")->onLeftButtonClick(     (EventHandler) &PlayerEditState::onDecreaseStrengthButtonClick);
    _buttons->at("stats_perception_increase")->onLeftButtonClick(   (EventHandler) &PlayerEditState::onIncreasePerceptionButtonClick);
    _buttons->at("stats_perception_decrease")->onLeftButtonClick(   (EventHandler) &PlayerEditState::onDecreasePerceptionButtonClick);
    _buttons->at("stats_endurance_increase")->onLeftButtonClick(    (EventHandler) &PlayerEditState::onIncreaseEnduranceButtonClick);
    _buttons->at("stats_endurance_decrease")->onLeftButtonClick(    (EventHandler) &PlayerEditState::onDecreaseEnduranceButtonClick);
    _buttons->at("stats_charisma_increase")->onLeftButtonClick(     (EventHandler) &PlayerEditState::onIncreaseCharismaButtonClick);
    _buttons->at("stats_charisma_decrease")->onLeftButtonClick(     (EventHandler) &PlayerEditState::onDecreaseCharismaButtonClick);
    _buttons->at("stats_intelligence_increase")->onLeftButtonClick( (EventHandler) &PlayerEditState::onIncreaseIntelligenceButtonClick);
    _buttons->at("stats_intelligence_decrease")->onLeftButtonClick( (EventHandler) &PlayerEditState::onDecreaseIntelligenceButtonClick);
    _buttons->at("stats_agility_increase")->onLeftButtonClick(      (EventHandler) &PlayerEditState::onIncreaseAgilityButtonClick);
    _buttons->at("stats_agility_decrease")->onLeftButtonClick(      (EventHandler) &PlayerEditState::onDecreaseAgilityButtonClick);
    _buttons->at("stats_luck_increase")->onLeftButtonClick(         (EventHandler) &PlayerEditState::onIncreaseLuckButtonClick);
    _buttons->at("stats_luck_decrease")->onLeftButtonClick(         (EventHandler) &PlayerEditState::onDecreaseLuckButtonClick);

    _masks->at("stats_strength")->onLeftButtonClick(     (EventHandler) &PlayerEditState::onStrengthSelected);
    _masks->at("stats_perception")->onLeftButtonClick(   (EventHandler) &PlayerEditState::onPerceptionSelected);
    _masks->at("stats_endurance")->onLeftButtonClick(    (EventHandler) &PlayerEditState::onEnduranceSelected);
    _masks->at("stats_charisma")->onLeftButtonClick(     (EventHandler) &PlayerEditState::onCharismaSelected);
    _masks->at("stats_intelligence")->onLeftButtonClick( (EventHandler) &PlayerEditState::onIntelligenceSelected);
    _masks->at("stats_agility")->onLeftButtonClick(      (EventHandler) &PlayerEditState::onAgilitySelected);
    _masks->at("stats_luck")->onLeftButtonClick(         (EventHandler) &PlayerEditState::onLuckSelected);


    add(_background);

    // add buttons to the state
    {
        std::map<std::string, ImageButton *>::iterator it;
        //for(it = _buttons->begin(); it != _buttons->end(); ++it) add(it->second);
    }
    // add labels to the state
    {
        std::map<std::string, TextArea *>::iterator it;
        for(it = _labels->begin(); it != _labels->end(); ++it) add(it->second);
    }
    // add counters to the state
    {
        std::map<std::string, BigCounter *>::iterator it;
        //for(it = _counters->begin(); it != _counters->end(); ++it) add(it->second);
    }
    // add hidden masks
    {
        std::map<std::string, HiddenMask *>::iterator it;
        for(it = _masks->begin(); it != _masks->end(); ++it)
        {
            it->second->setBorderColor(0xFFFF0000);
            it->second->setVisible(true);
            //add(it->second);
        }
    }

}

PlayerEditState::~PlayerEditState()
{
    delete _checkedLabels;
    delete _labels;
    delete _buttons;
    delete _counters;
    delete _masks;
}

TextArea * PlayerEditState::_addLabel(std::string name, TextArea * label)
{
    _labels->insert(std::pair<std::string,TextArea *>(name, label));
    return label;
}

ImageButton * PlayerEditState::_addButton(std::string name, ImageButton * button)
{
    _buttons->insert(std::pair<std::string,ImageButton *>(name, button));
    return button;
}

BigCounter * PlayerEditState::_addCounter(std::string name, BigCounter * counter)
{
    _counters->insert(std::pair<std::string,BigCounter *>(name, counter));
    return counter;
}

HiddenMask * PlayerEditState::_addMask(std::string name, HiddenMask * mask)
{
    _masks->insert(std::pair<std::string,HiddenMask *>(name, mask));
    return mask;
}

void PlayerEditState::think()
{
    //std::cout << _game->resourceManager()->surface("art/intrface/edtrcrte.frm")->width() << std::endl;
    _background->loadFromSurface(_game->resourceManager()->surface("art/intrface/edtrcrte.frm"));
    return;
    // primary stats labels
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
        _labels->at("stats_strength")->setText(msg->message(199 + _game->player()->strength));
        _labels->at("stats_perception")->setText(msg->message(199 + _game->player()->perception));
        _labels->at("stats_endurance")->setText(msg->message(199 + _game->player()->endurance));
        _labels->at("stats_charisma")->setText(msg->message(199 + _game->player()->charisma));
        _labels->at("stats_intelligence")->setText(msg->message(199 + _game->player()->intelligence));
        _labels->at("stats_agility")->setText(msg->message(199 + _game->player()->agility));
        _labels->at("stats_luck")->setText(msg->message(199 + _game->player()->luck));
    }
    // primary stats counters

    /*
    _counters->at("stats_strength")->setNumber(_game->player()->strength);
    _counters->at("stats_perception")->setNumber(_game->player()->perception);
    _counters->at("stats_endurance")->setNumber(_game->player()->endurance);
    _counters->at("stats_charisma")->setNumber(_game->player()->charisma);
    _counters->at("stats_intelligence")->setNumber(_game->player()->intelligence);
    _counters->at("stats_agility")->setNumber(_game->player()->agility);
    _counters->at("stats_luck")->setNumber(_game->player()->luck);
    _counters->at("stats_points")->setNumber(_game->player()->freeStatsPoints);
    */

}

void PlayerEditState::onIncreaseStrengthButtonClick()
{
    onStrengthSelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->strength < 10)
    {
        _game->player()->strength++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseStrengthButtonClick()
{
    onStrengthSelected();
    if (_game->player()->strength > 2)
    {
        _game->player()->strength--;
        _game->player()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreasePerceptionButtonClick()
{
    onPerceptionSelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->perception < 10)
    {
        _game->player()->perception++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreasePerceptionButtonClick()
{
    onPerceptionSelected();
    if (_game->player()->perception > 2)
    {
        _game->player()->perception--;
        _game->player()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseEnduranceButtonClick()
{
    onEnduranceSelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->endurance < 10)
    {
        _game->player()->endurance++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseEnduranceButtonClick()
{
    onEnduranceSelected();
    if (_game->player()->endurance > 2)
    {
        _game->player()->endurance--;
        _game->player()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseCharismaButtonClick()
{
    onCharismaSelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->charisma < 10)
    {
        _game->player()->charisma++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseCharismaButtonClick()
{
    onCharismaSelected();
    if (_game->player()->charisma > 2)
    {
        _game->player()->charisma--;
        _game->player()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseIntelligenceButtonClick()
{
    onIntelligenceSelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->intelligence < 10)
    {
        _game->player()->intelligence++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseIntelligenceButtonClick()
{
    onIntelligenceSelected();
    if (_game->player()->intelligence > 2)
    {
        _game->player()->intelligence--;
        _game->player()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseAgilityButtonClick()
{
    onAgilitySelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->agility < 10)
    {
        _game->player()->agility++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseAgilityButtonClick()
{
    onAgilitySelected();
    if (_game->player()->agility > 2)
    {
        _game->player()->agility--;
        _game->player()->freeStatsPoints++;
    }
}

void PlayerEditState::onIncreaseLuckButtonClick()
{
    onLuckSelected();
    if (_game->player()->freeStatsPoints == 0) return;
    if (_game->player()->luck < 10)
    {
        _game->player()->luck++;
        _game->player()->freeStatsPoints--;
    }
}

void PlayerEditState::onDecreaseLuckButtonClick()
{
    onLuckSelected();
    if (_game->player()->luck > 2)
    {
        _game->player()->luck--;
        _game->player()->freeStatsPoints++;
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
