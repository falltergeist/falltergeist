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
    _selectedLabel = 0;
    _labels = new std::map<std::string, TextArea *>;
    _counters = new std::map<std::string, BigCounter *>;
    _buttons = new std::map<std::string, ImageButton *>;
    _masks= new std::map<std::string, HiddenMask *>;

    Surface * background = new Surface(_game->resourceManager()->surface("art/intrface/edtrcrte.frm"));

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
        // Free skill points counts
        _addCounter("skills_points",       new BigCounter(522, 228));
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
        _addLabel("traits_9",  new TextArea(msg->message(108), 169, 352))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_10", new TextArea(msg->message(109), 169, 366))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_11", new TextArea(msg->message(110), 169, 380))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_12", new TextArea(msg->message(111), 169, 393))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_13", new TextArea(msg->message(112), 169, 407))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_14", new TextArea(msg->message(113), 169, 420))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_15", new TextArea(msg->message(114), 169, 433))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
        _addLabel("traits_16", new TextArea(msg->message(115), 169, 447))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
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

    // Skills buttons
    {
        const char * on  = "art/intrface/tgsklon.frm";
        const char * off = "art/intrface/tgskloff.frm";
        _addButton("skills_1",  new ImageButton(off, on, 347,  26));
        _addButton("skills_2",  new ImageButton(off, on, 347,  26 + 11));
        _addButton("skills_3",  new ImageButton(off, on, 347,  26 + 11*2));
        _addButton("skills_4",  new ImageButton(off, on, 347,  26 + 11*3));
        _addButton("skills_5",  new ImageButton(off, on, 347,  26 + 11*4));
        _addButton("skills_6",  new ImageButton(off, on, 347,  26 + 11*5));
        _addButton("skills_7",  new ImageButton(off, on, 347,  26 + 11*6));
        _addButton("skills_8",  new ImageButton(off, on, 347,  26 + 11*7));
        _addButton("skills_9",  new ImageButton(off, on, 347,  26 + 11*8));
        _addButton("skills_10", new ImageButton(off, on, 347,  26 + 11*9));
        _addButton("skills_11", new ImageButton(off, on, 347,  26 + 11*10));
        _addButton("skills_12", new ImageButton(off, on, 347,  26 + 11*11));
        _addButton("skills_13", new ImageButton(off, on, 347,  26 + 11*12));
        _addButton("skills_14", new ImageButton(off, on, 347,  26 + 11*13));
        _addButton("skills_15", new ImageButton(off, on, 347,  26 + 11*14));
        _addButton("skills_16", new ImageButton(off, on, 347,  26 + 11*15));
        _addButton("skills_17", new ImageButton(off, on, 347,  26 + 11*16));
        _addButton("skills_18", new ImageButton(off, on, 347,  26 + 11*17));
    }
    // Skills labels
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/skill.msg");
        _addLabel("skills_1",  new TextArea(msg->message(100), 377, 27))->setWidth(240);
        _addLabel("skills_2",  new TextArea(msg->message(101), 377, 27 + 11))->setWidth(240);
        _addLabel("skills_3",  new TextArea(msg->message(102), 377, 27 + 11*2))->setWidth(240);
        _addLabel("skills_4",  new TextArea(msg->message(103), 377, 27 + 11*3))->setWidth(240);
        _addLabel("skills_5",  new TextArea(msg->message(104), 377, 27 + 11*4))->setWidth(240);
        _addLabel("skills_6",  new TextArea(msg->message(105), 377, 27 + 11*5))->setWidth(240);
        _addLabel("skills_7",  new TextArea(msg->message(106), 377, 27 + 11*6))->setWidth(240);
        _addLabel("skills_8",  new TextArea(msg->message(107), 377, 27 + 11*7))->setWidth(240);
        _addLabel("skills_9",  new TextArea(msg->message(108), 377, 27 + 11*8))->setWidth(240);
        _addLabel("skills_10", new TextArea(msg->message(109), 377, 27 + 11*9))->setWidth(240);
        _addLabel("skills_11", new TextArea(msg->message(110), 377, 27 + 11*10))->setWidth(240);
        _addLabel("skills_12", new TextArea(msg->message(111), 377, 27 + 11*11))->setWidth(240);
        _addLabel("skills_13", new TextArea(msg->message(112), 377, 27 + 11*12))->setWidth(240);
        _addLabel("skills_14", new TextArea(msg->message(113), 377, 27 + 11*13))->setWidth(240);
        _addLabel("skills_15", new TextArea(msg->message(114), 377, 27 + 11*14))->setWidth(240);
        _addLabel("skills_16", new TextArea(msg->message(115), 377, 27 + 11*15))->setWidth(240);
        _addLabel("skills_17", new TextArea(msg->message(116), 377, 27 + 11*16))->setWidth(240);
        _addLabel("skills_18", new TextArea(msg->message(117), 377, 27 + 11*17))->setWidth(240);
    }

    add(background);

    // add buttons to the state
    {
        std::map<std::string, ImageButton *>::iterator it;
        for(it = _buttons->begin(); it != _buttons->end(); ++it)
        {
            it->second->onLeftButtonClick((EventHandler) &PlayerEditState::onButtonClick);
            add(it->second);
        }
    }
    // add labels to the state
    {
        // reverse iterator to change drawing order
        std::map<std::string, TextArea *>::reverse_iterator it;
        for(it = _labels->rbegin(); it != _labels->rend(); ++it)
        {
            it->second->setBackgroundColor(0x01000000);
            it->second->onLeftButtonClick((EventHandler) &PlayerEditState::onLabelClick);
            add(it->second);
        }
    }
    // add counters to the state
    {
        std::map<std::string, BigCounter *>::iterator it;
        for(it = _counters->begin(); it != _counters->end(); ++it) add(it->second);
    }
    // add hidden masks
    {
        std::map<std::string, HiddenMask *>::iterator it;
        for(it = _masks->begin(); it != _masks->end(); ++it)
        {
            it->second->setBorderColor(0xFFFF0000);
            it->second->setVisible(true);
            it->second->onLeftButtonClick((EventHandler) &PlayerEditState::onMaskClick);
            add(it->second);
        }
    }

}

PlayerEditState::~PlayerEditState()
{
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
    // primary stats labels
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
        std::map<std::string, TextArea *>::iterator it;
        for(it = _labels->begin(); it != _labels->end(); ++it)
        {
            std::string name = it->first;
            // default colors
            if (name == "stats_strength" || name == "stats_perception" || name == "stats_endurance" || name == "stats_charisma" ||
                name == "stats_intelligence" || name == "stats_agility" || name == "stats_luck")
            {
                it->second->setColor(0xFF00FF00);
            }

            if (name == "traits_1" || name == "traits_2" || name == "traits_3" || name == "traits_4" || name == "traits_5" || name == "traits_6" ||
                name == "traits_7" || name == "traits_8" || name == "traits_9" || name == "traits_10" || name == "traits_11" || name == "traits_12" ||
                name == "traits_13" || name == "traits_14" || name == "traits_15" || name == "traits_16" )
            {
                it->second->setColor(0xFF00FF00);
            }

            if (name == "skills_1" || name == "skills_2" || name == "skills_3" || name == "skills_4" || name == "skills_5" || name == "skills_6" ||
                name == "skills_7" || name == "skills_8" || name == "skills_9" || name == "skills_10" || name == "skills_11" || name == "skills_12" ||
                name == "skills_13" || name == "skills_14" || name == "skills_15" || name == "skills_16" || name == "skills_17" || name == "skills_18" )
            {
                it->second->setColor(0xFF00FF00);
            }

            if (name == "traits_1" && _game->player()->trait(Player::TRAITS_1) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_2" && _game->player()->trait(Player::TRAITS_2) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_3" && _game->player()->trait(Player::TRAITS_3) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_4" && _game->player()->trait(Player::TRAITS_4) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_5" && _game->player()->trait(Player::TRAITS_5) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_6" && _game->player()->trait(Player::TRAITS_6) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_7" && _game->player()->trait(Player::TRAITS_7) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_8" && _game->player()->trait(Player::TRAITS_8) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_9" && _game->player()->trait(Player::TRAITS_9) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_10" && _game->player()->trait(Player::TRAITS_10) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_11" && _game->player()->trait(Player::TRAITS_11) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_12" && _game->player()->trait(Player::TRAITS_12) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_13" && _game->player()->trait(Player::TRAITS_13) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_14" && _game->player()->trait(Player::TRAITS_14) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_15" && _game->player()->trait(Player::TRAITS_15) == 1) it->second->setColor(0xFF999999);
            if (name == "traits_16" && _game->player()->trait(Player::TRAITS_16) == 1) it->second->setColor(0xFF999999);

            if (name == "skills_1" && _game->player()->skill(Player::SKILLS_1) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_2" && _game->player()->skill(Player::SKILLS_2) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_3" && _game->player()->skill(Player::SKILLS_3) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_4" && _game->player()->skill(Player::SKILLS_4) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_5" && _game->player()->skill(Player::SKILLS_5) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_6" && _game->player()->skill(Player::SKILLS_6) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_7" && _game->player()->skill(Player::SKILLS_7) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_8" && _game->player()->skill(Player::SKILLS_8) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_9" && _game->player()->skill(Player::SKILLS_9) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_10" && _game->player()->skill(Player::SKILLS_10) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_11" && _game->player()->skill(Player::SKILLS_11) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_12" && _game->player()->skill(Player::SKILLS_12) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_13" && _game->player()->skill(Player::SKILLS_13) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_14" && _game->player()->skill(Player::SKILLS_14) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_15" && _game->player()->skill(Player::SKILLS_15) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_16" && _game->player()->skill(Player::SKILLS_16) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_17" && _game->player()->skill(Player::SKILLS_17) == 1) it->second->setColor(0xFF999999);
            if (name == "skills_18" && _game->player()->skill(Player::SKILLS_18) == 1) it->second->setColor(0xFF999999);

            // selected color
            if (_selectedLabel == it->second)
            {
                if (name == "stats_strength" || name == "stats_perception" || name == "stats_endurance" || name == "stats_charisma" ||
                    name == "stats_intelligence" || name == "stats_agility" || name == "stats_luck")
                {
                    it->second->setColor(0xFFFDF998);
                }
                if (name == "traits_1" || name == "traits_2" || name == "traits_3" || name == "traits_4" || name == "traits_5" || name == "traits_6" ||
                    name == "traits_7" || name == "traits_8" || name == "traits_9" || name == "traits_10" || name == "traits_11" || name == "traits_12" ||
                    name == "traits_13" || name == "traits_14" || name == "traits_15" || name == "traits_16" )
                {
                    it->second->setColor(0xFFFDF998);
                }

                if (name == "skills_1" || name == "skills_2" || name == "skills_3" || name == "skills_4" || name == "skills_5" || name == "skills_6" ||
                    name == "skills_7" || name == "skills_8" || name == "skills_9" || name == "skills_10" || name == "skills_11" || name == "skills_12" ||
                    name == "skills_13" || name == "skills_14" || name == "skills_15" || name == "skills_16" || name == "skills_17" || name == "skills_18" )
                {
                    it->second->setColor(0xFFFDF998);
                }

                if (name == "traits_1" && _game->player()->trait(Player::TRAITS_1) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_2" && _game->player()->trait(Player::TRAITS_2) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_3" && _game->player()->trait(Player::TRAITS_3) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_4" && _game->player()->trait(Player::TRAITS_4) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_5" && _game->player()->trait(Player::TRAITS_5) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_6" && _game->player()->trait(Player::TRAITS_6) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_7" && _game->player()->trait(Player::TRAITS_7) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_8" && _game->player()->trait(Player::TRAITS_8) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_9" && _game->player()->trait(Player::TRAITS_9) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_10" && _game->player()->trait(Player::TRAITS_10) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_11" && _game->player()->trait(Player::TRAITS_11) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_12" && _game->player()->trait(Player::TRAITS_12) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_13" && _game->player()->trait(Player::TRAITS_13) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_14" && _game->player()->trait(Player::TRAITS_14) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_15" && _game->player()->trait(Player::TRAITS_15) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "traits_16" && _game->player()->trait(Player::TRAITS_16) == 1) it->second->setColor(0xFFFFFFFF);

                if (name == "skills_1" && _game->player()->skill(Player::SKILLS_1) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_2" && _game->player()->skill(Player::SKILLS_2) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_3" && _game->player()->skill(Player::SKILLS_3) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_4" && _game->player()->skill(Player::SKILLS_4) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_5" && _game->player()->skill(Player::SKILLS_5) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_6" && _game->player()->skill(Player::SKILLS_6) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_7" && _game->player()->skill(Player::SKILLS_7) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_8" && _game->player()->skill(Player::SKILLS_8) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_9" && _game->player()->skill(Player::SKILLS_9) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_10" && _game->player()->skill(Player::SKILLS_10) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_11" && _game->player()->skill(Player::SKILLS_11) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_12" && _game->player()->skill(Player::SKILLS_12) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_13" && _game->player()->skill(Player::SKILLS_13) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_14" && _game->player()->skill(Player::SKILLS_14) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_15" && _game->player()->skill(Player::SKILLS_15) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_16" && _game->player()->skill(Player::SKILLS_16) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_17" && _game->player()->skill(Player::SKILLS_17) == 1) it->second->setColor(0xFFFFFFFF);
                if (name == "skills_18" && _game->player()->skill(Player::SKILLS_18) == 1) it->second->setColor(0xFFFFFFFF);

            }
        }

        _labels->at("stats_strength")->setText(msg->message(199 + _game->player()->strength()));
        _labels->at("stats_perception")->setText(msg->message(199 + _game->player()->perception()));
        _labels->at("stats_endurance")->setText(msg->message(199 + _game->player()->endurance()));
        _labels->at("stats_charisma")->setText(msg->message(199 + _game->player()->charisma()));
        _labels->at("stats_intelligence")->setText(msg->message(199 + _game->player()->intelligence()));
        _labels->at("stats_agility")->setText(msg->message(199 + _game->player()->agility()));
        _labels->at("stats_luck")->setText(msg->message(199 + _game->player()->luck()));
    }

    // primary stats counters
    _counters->at("stats_strength")->setNumber(_game->player()->strength());
    _counters->at("stats_perception")->setNumber(_game->player()->perception());
    _counters->at("stats_endurance")->setNumber(_game->player()->endurance());
    _counters->at("stats_charisma")->setNumber(_game->player()->charisma());
    _counters->at("stats_intelligence")->setNumber(_game->player()->intelligence());
    _counters->at("stats_agility")->setNumber(_game->player()->agility());
    _counters->at("stats_luck")->setNumber(_game->player()->luck());
    _counters->at("stats_points")->setNumber(_game->player()->characterPoints());
    _counters->at("skills_points")->setNumber(_game->player()->skillPoints());


}

void PlayerEditState::onButtonClick(Event * event)
{
    for (unsigned int i = 0; i != 18; ++i)
    {
        std::cout << "SKILL "<< i << ": " << (int) _game->player()->skill(i) << std::endl;
    }

    std::map<std::string, ImageButton *>::iterator it;
    for(it = _buttons->begin(); it != _buttons->end(); ++it)
    {
        if (it->second == event->sender())
        {
            std::string name = it->first;
            if (name == "stats_strength_increase")
            {
                _selectedLabel = _labels->at("stats_strength");
                _game->player()->statsIncrease(Player::STATS_STRENGTH);
            }
            if (name == "stats_strength_decrease")
            {
                _selectedLabel = _labels->at("stats_strength");
                _game->player()->statsDecrease(Player::STATS_STRENGTH);
            }
            if (name == "stats_perception_increase")
            {
                _selectedLabel = _labels->at("stats_perception");
                _game->player()->statsIncrease(Player::STATS_PERCEPTION);
            }
            if (name == "stats_perception_decrease")
            {
                _selectedLabel = _labels->at("stats_perception");
                _game->player()->statsDecrease(Player::STATS_PERCEPTION);
            }
            if (name == "stats_endurance_increase")
            {
                _selectedLabel = _labels->at("stats_endurance");
                _game->player()->statsIncrease(Player::STATS_ENDURANCE);
            }
            if (name == "stats_endurance_decrease")
            {
                _selectedLabel = _labels->at("stats_endurance");
                _game->player()->statsDecrease(Player::STATS_ENDURANCE);
            }
            if (name == "stats_charisma_increase")
            {
                _selectedLabel = _labels->at("stats_charisma");
                _game->player()->statsIncrease(Player::STATS_CHARISMA);
            }
            if (name == "stats_charisma_decrease")
            {
                _selectedLabel = _labels->at("stats_charisma");
                _game->player()->statsDecrease(Player::STATS_CHARISMA);
            }
            if (name == "stats_intelligence_increase")
            {
                _selectedLabel = _labels->at("stats_intelligence");
                _game->player()->statsIncrease(Player::STATS_INTELLIGENCE);
            }
            if (name == "stats_intelligence_decrease")
            {
                _selectedLabel = _labels->at("stats_intelligence");
                _game->player()->statsDecrease(Player::STATS_INTELLIGENCE);
            }
            if (name == "stats_agility_increase")
            {
                _selectedLabel = _labels->at("stats_agility");
                _game->player()->statsIncrease(Player::STATS_AGILITY);
            }
            if (name == "stats_agility_decrease")
            {
                _selectedLabel = _labels->at("stats_agility");
                _game->player()->statsDecrease(Player::STATS_AGILITY);
            }
            if (name == "stats_luck_increase")
            {
                _selectedLabel = _labels->at("stats_luck");
                _game->player()->statsIncrease(Player::STATS_LUCK);
            }
            if (name == "stats_luck_decrease")
            {
                _selectedLabel = _labels->at("stats_luck");
                _game->player()->statsDecrease(Player::STATS_LUCK);
            }

            if (name == "traits_1")
            {
                _selectedLabel = _labels->at("traits_1");
                _game->player()->traitToggle(Player::TRAITS_1);
            }
            if (name == "traits_2")
            {
                _selectedLabel = _labels->at("traits_2");
                _game->player()->traitToggle(Player::TRAITS_2);
            }
            if (name == "traits_3")
            {
                _selectedLabel = _labels->at("traits_3");
                _game->player()->traitToggle(Player::TRAITS_3);
            }
            if (name == "traits_4")
            {
                _selectedLabel = _labels->at("traits_4");
                _game->player()->traitToggle(Player::TRAITS_4);
            }
            if (name == "traits_5")
            {
                _selectedLabel = _labels->at("traits_5");
                _game->player()->traitToggle(Player::TRAITS_5);
            }
            if (name == "traits_6")
            {
                _selectedLabel = _labels->at("traits_6");
                _game->player()->traitToggle(Player::TRAITS_6);
            }
            if (name == "traits_7")
            {
                _selectedLabel = _labels->at("traits_7");
                _game->player()->traitToggle(Player::TRAITS_7);
            }
            if (name == "traits_8")
            {
                _selectedLabel = _labels->at("traits_8");
                _game->player()->traitToggle(Player::TRAITS_8);
            }
            if (name == "traits_9")
            {
                _selectedLabel = _labels->at("traits_9");
                _game->player()->traitToggle(Player::TRAITS_9);
            }
            if (name == "traits_10")
            {
                _selectedLabel = _labels->at("traits_10");
                _game->player()->traitToggle(Player::TRAITS_10);
            }
            if (name == "traits_11")
            {
                _selectedLabel = _labels->at("traits_11");
                _game->player()->traitToggle(Player::TRAITS_11);
            }
            if (name == "traits_12")
            {
                _selectedLabel = _labels->at("traits_12");
                _game->player()->traitToggle(Player::TRAITS_12);
            }
            if (name == "traits_13")
            {
                _selectedLabel = _labels->at("traits_13");
                _game->player()->traitToggle(Player::TRAITS_13);
            }
            if (name == "traits_14")
            {
                _selectedLabel = _labels->at("traits_14");
                _game->player()->traitToggle(Player::TRAITS_14);
            }
            if (name == "traits_15")
            {
                _selectedLabel = _labels->at("traits_15");
                _game->player()->traitToggle(Player::TRAITS_15);
            }
            if (name == "traits_16")
            {
                _selectedLabel = _labels->at("traits_16");
                _game->player()->traitToggle(Player::TRAITS_16);
            }
            if (name == "skills_1")
            {
                _selectedLabel = _labels->at("skills_1");
                _game->player()->skillToggle(Player::SKILLS_1);
            }
            if (name == "skills_2")
            {
                _selectedLabel = _labels->at("skills_2");
                _game->player()->skillToggle(Player::SKILLS_2);
            }
            if (name == "skills_3")
            {
                _selectedLabel = _labels->at("skills_3");
                _game->player()->skillToggle(Player::SKILLS_3);
            }
            if (name == "skills_4")
            {
                _selectedLabel = _labels->at("skills_4");
                _game->player()->skillToggle(Player::SKILLS_4);
            }
            if (name == "skills_5")
            {
                _selectedLabel = _labels->at("skills_5");
                _game->player()->skillToggle(Player::SKILLS_5);
            }
            if (name == "skills_6")
            {
                _selectedLabel = _labels->at("skills_6");
                _game->player()->skillToggle(Player::SKILLS_6);
            }
            if (name == "skills_7")
            {
                _selectedLabel = _labels->at("skills_7");
                _game->player()->skillToggle(Player::SKILLS_7);
            }
            if (name == "skills_8")
            {
                _selectedLabel = _labels->at("skills_8");
                _game->player()->skillToggle(Player::SKILLS_8);
            }
            if (name == "skills_9")
            {
                _selectedLabel = _labels->at("skills_9");
                _game->player()->skillToggle(Player::SKILLS_9);
            }
            if (name == "skills_10")
            {
                _selectedLabel = _labels->at("skills_10");
                _game->player()->skillToggle(Player::SKILLS_10);
            }
            if (name == "skills_11")
            {
                _selectedLabel = _labels->at("skills_11");
                _game->player()->skillToggle(Player::SKILLS_11);
            }
            if (name == "skills_12")
            {
                _selectedLabel = _labels->at("skills_12");
                _game->player()->skillToggle(Player::SKILLS_12);
            }
            if (name == "skills_13")
            {
                _selectedLabel = _labels->at("skills_13");
                _game->player()->skillToggle(Player::SKILLS_13);
            }
            if (name == "skills_14")
            {
                _selectedLabel = _labels->at("skills_14");
                _game->player()->skillToggle(Player::SKILLS_14);
            }
            if (name == "skills_15")
            {
                _selectedLabel = _labels->at("skills_15");
                _game->player()->skillToggle(Player::SKILLS_15);
            }
            if (name == "skills_16")
            {
                _selectedLabel = _labels->at("skills_16");
                _game->player()->skillToggle(Player::SKILLS_16);
            }
            if (name == "skills_17")
            {
                _selectedLabel = _labels->at("skills_17");
                _game->player()->skillToggle(Player::SKILLS_17);
            }
            if (name == "skills_18")
            {
                _selectedLabel = _labels->at("skills_18");
                _game->player()->skillToggle(Player::SKILLS_18);
            }
        }
    }
}

void PlayerEditState::onLabelClick(Event * event)
{
    std::map<std::string, TextArea *>::iterator it;
    for(it = _labels->begin(); it != _labels->end(); ++it)
    {
        if (it->second == event->sender())
        {
            _selectedLabel = _labels->at(it->first);
        }
    }
}

void PlayerEditState::onMaskClick(Event * event)
{
    std::map<std::string, HiddenMask *>::iterator it;
    for(it = _masks->begin(); it != _masks->end(); ++it)
    {
        if (it->second == event->sender())
        {
            std::string name = it->first;
            if (name == "stats_strength")
            {
                _selectedLabel = _labels->at("stats_strength");
            }
            if (name == "stats_perception")
            {
                _selectedLabel = _labels->at("stats_perception");
            }
            if (name == "stats_endurance")
            {
                _selectedLabel = _labels->at("stats_endurance");
            }
            if (name == "stats_charisma")
            {
                _selectedLabel = _labels->at("stats_charisma");
            }
            if (name == "stats_intelligence")
            {
                _selectedLabel = _labels->at("stats_intelligence");
            }
            if (name == "stats_agility")
            {
                _selectedLabel = _labels->at("stats_agility");
            }
            if (name == "stats_luck")
            {
                _selectedLabel = _labels->at("stats_luck");
            }
        }
    }
}

}
