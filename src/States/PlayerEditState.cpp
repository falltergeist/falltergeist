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
#include <sstream>

namespace Falltergeist
{

PlayerEditState::PlayerEditState(Game * game) : State(game)
{
    _labels = new std::map<std::string, TextArea *>;
    _counters = new std::map<std::string, BigCounter *>;
    _buttons = new std::map<std::string, ImageButton *>;
    _masks = new std::map<std::string, HiddenMask *>;
    _titles = new std::map<std::string, std::string>;
    _descriptions = new std::map<std::string, std::string>;
    _images = new std::map<std::string, Surface *>;


    // Stats titles & descriptions
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/stat.msg");
        for (unsigned int i = 0; i != 16; ++i)
        {
            std::stringstream ss;
            ss << "stats_" << (i+1);
            _addTitle(ss.str(), msg->message(100 + i)->text());
            _addDescription(ss.str(), msg->message(200 + i)->text());
        }
    }

    // Traits titles & descriptions
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/trait.msg");
        for (unsigned int i = 0; i != 16; ++i)
        {
            std::stringstream ss;
            ss << "traits_" << (i+1);
            _addTitle(ss.str(), msg->message(100 + i)->text());
            _addDescription(ss.str(), msg->message(200 + i)->text());
        }
    }

    // Skills titles & descriptions
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/skill.msg");
        for (unsigned int i = 0; i != 18; ++i)
        {
            std::stringstream ss;
            ss << "skills_" << (i+1);
            _addTitle(ss.str(), msg->message(100 + i)->text());
            _addDescription(ss.str(), msg->message(200 + i)->text());
        }
    }

    // Images
    {
        const char * stats[] = { "strength", "perceptn", "endur", "charisma", "intel", "agility", "luck"};
        for (unsigned int i = 0; i != 7; ++i)
        {
            std::stringstream name;
            name << "stats_" << (i+1);

            std::stringstream filename;
            filename << "art/skilldex/" << stats[i] << ".frm";
            Surface * surface = _game->resourceManager()->surface(filename.str().c_str());
            _addImage(name.str(), surface);
        }

        const char * traits[] = { "fastmeta", "bruiser", "smlframe", "onehand", "finesse", "kamikaze", "heavyhnd", "fastshot",
                                  "bldmess", "jinxed", "goodnatr", "addict", "drugrest", "empathy", "skilled", "gifted"};
        for (unsigned int i = 0; i != 16; ++i)
        {
            std::stringstream name;
            name << "traits_" << (i+1);

            std::stringstream filename;
            filename << "art/skilldex/" << traits[i] << ".frm";
            Surface * surface = _game->resourceManager()->surface(filename.str().c_str());
            _addImage(name.str(), surface);
        }

        const char * skills[] = { "gunsml", "gunbig", "energywp", "unarmed", "melee", "throwing", "firstaid", "doctor", "sneak",
                                 "lockpick", "steal", "traps", "science", "repair", "speech", "barter", "gambling", "outdoors"};
        for (unsigned int i = 0; i != 18; ++i)
        {
            std::stringstream name;
            name << "skills_" << (i+1);

            std::stringstream filename;
            filename << "art/skilldex/" << skills[i] << ".frm";
            Surface * surface = _game->resourceManager()->surface(filename.str().c_str());
            _addImage(name.str(), surface);
        }

    }

    Surface * background = new Surface(_game->resourceManager()->surface("art/intrface/edtrcrte.frm"));

    // Primary stats buttons
    {
        const char * plusOn   = "art/intrface/splson.frm";
        const char * plusOff  = "art/intrface/splsoff.frm";
        const char * minusOn  = "art/intrface/snegon.frm";
        const char * minusOff = "art/intrface/snegoff.frm";

        _addButton("stats_1_increase", new ImageButton(plusOff,  plusOn,  149, 38));
        _addButton("stats_1_decrease", new ImageButton(minusOff, minusOn, 149, 49));
        _addButton("stats_2_increase", new ImageButton(plusOff,  plusOn,  149, 71));
        _addButton("stats_2_decrease", new ImageButton(minusOff, minusOn, 149, 82));
        _addButton("stats_3_increase", new ImageButton(plusOff,  plusOn,  149, 104));
        _addButton("stats_3_decrease", new ImageButton(minusOff, minusOn, 149, 115));
        _addButton("stats_4_increase", new ImageButton(plusOff,  plusOn,  149, 137));
        _addButton("stats_4_decrease", new ImageButton(minusOff, minusOn, 149, 148));
        _addButton("stats_5_increase", new ImageButton(plusOff,  plusOn,  149, 170));
        _addButton("stats_5_decrease", new ImageButton(minusOff, minusOn, 149, 181));
        _addButton("stats_6_increase", new ImageButton(plusOff,  plusOn,  149, 203));
        _addButton("stats_6_decrease", new ImageButton(minusOff, minusOn, 149, 214));
        _addButton("stats_7_increase", new ImageButton(plusOff,  plusOn,  149, 236));
        _addButton("stats_7_decrease", new ImageButton(minusOff, minusOn, 149, 247));
    }
    // Primary stats labels
    {
        _addLabel("stats_1", new TextArea(102, 46));
        _addLabel("stats_2", new TextArea(102, 79));
        _addLabel("stats_3", new TextArea(102, 112));
        _addLabel("stats_4", new TextArea(102, 145));
        _addLabel("stats_5", new TextArea(102, 178));
        _addLabel("stats_6", new TextArea(102, 211));
        _addLabel("stats_7", new TextArea(102, 244));
    }
    // Primary stats counters
    {
        _addCounter("stats_1", new BigCounter(59, 37));
        _addCounter("stats_2", new BigCounter(59, 70));
        _addCounter("stats_3", new BigCounter(59, 103));
        _addCounter("stats_4", new BigCounter(59, 136));
        _addCounter("stats_5", new BigCounter(59, 169));
        _addCounter("stats_6", new BigCounter(59, 202));
        _addCounter("stats_7", new BigCounter(59, 235));
        // Free stats points counter
        _addCounter("statsPoints", new BigCounter(126, 282));
        // Free skill points counts
        _addCounter("skillsPoints", new BigCounter(522, 228));
    }

    // Primaty stats hidden masks
    {
        _addMask("stats_1", new HiddenMask(133, 29, 14, 36));
        _addMask("stats_2", new HiddenMask(133, 29, 14, 36 + 33));
        _addMask("stats_3", new HiddenMask(133, 29, 14, 36 + 33*2));
        _addMask("stats_4", new HiddenMask(133, 29, 14, 36 + 33*3));
        _addMask("stats_5", new HiddenMask(133, 29, 14, 36 + 33*4));
        _addMask("stats_6", new HiddenMask(133, 29, 14, 36 + 33*5));
        _addMask("stats_7", new HiddenMask(133, 29, 14, 36 + 33*6));
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

    _selectedImage = _images->at("stats_1");
    _selectedLabel = _labels->at("stats_1");
    _image = new Surface(_selectedImage);
    add(_image);

    _title = new TextArea(" ", 350,275);
    _title->setFont("font2.aaf");
    _title->setColor(0xFF000000);
    add(_title);
}

PlayerEditState::~PlayerEditState()
{
    delete _labels;
    delete _buttons;
    delete _counters;
    delete _masks;
    delete _titles;
    delete _descriptions;
    delete _images;
    delete _image;
    delete _title;
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

void PlayerEditState::_addTitle(std::string name, std::string title)
{
    _titles->insert(std::pair<std::string,std::string>(name, title));
}

void PlayerEditState::_addDescription(std::string name, std::string description)
{
    _descriptions->insert(std::pair<std::string,std::string>(name, description));
}

void PlayerEditState::_addImage(std::string name, Surface * image)
{
    _images->insert(std::pair<std::string,Surface *>(name, image));
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
            if (name.find("stats_") == 0 || name.find("traits_") == 0 || name.find("skills_") == 0)
            {
                it->second->setColor(0xFF00FF00);
            }

            if (name.find("traits_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                if (_game->player()->trait(number - 1) == 1) it->second->setColor(0xFF999999);
            }

            if (name.find("skills_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                if (_game->player()->skill(number - 1) == 1) it->second->setColor(0xFF999999);
            }

            // selected color
            if (_selectedLabel == it->second)
            {
                if (name.find("stats_") == 0 || name.find("traits_") == 0 || name.find("skills_") == 0)
                {
                    it->second->setColor(0xFFFDF998);
                }

                if (name.find("traits_") == 0)
                {
                    unsigned int number = atoi(name.substr(7).c_str());
                    if (_game->player()->trait(number - 1) == 1) it->second->setColor(0xFFFFFFFF);
                }

                if (name.find("skills_") == 0)
                {
                    unsigned int number = atoi(name.substr(7).c_str());
                    if (_game->player()->skill(number - 1) == 1) it->second->setColor(0xFFFFFFFF);
                }
            }
        }

        _labels->at("stats_1")->setText(msg->message(199 + _game->player()->strength()));
        _labels->at("stats_2")->setText(msg->message(199 + _game->player()->perception()));
        _labels->at("stats_3")->setText(msg->message(199 + _game->player()->endurance()));
        _labels->at("stats_4")->setText(msg->message(199 + _game->player()->charisma()));
        _labels->at("stats_5")->setText(msg->message(199 + _game->player()->intelligence()));
        _labels->at("stats_6")->setText(msg->message(199 + _game->player()->agility()));
        _labels->at("stats_7")->setText(msg->message(199 + _game->player()->luck()));
    }

    // primary stats counters
    _counters->at("stats_1")->setNumber(_game->player()->strength());
    _counters->at("stats_2")->setNumber(_game->player()->perception());
    _counters->at("stats_3")->setNumber(_game->player()->endurance());
    _counters->at("stats_4")->setNumber(_game->player()->charisma());
    _counters->at("stats_5")->setNumber(_game->player()->intelligence());
    _counters->at("stats_6")->setNumber(_game->player()->agility());
    _counters->at("stats_7")->setNumber(_game->player()->luck());
    _counters->at("statsPoints")->setNumber(_game->player()->characterPoints());
    _counters->at("skillsPoints")->setNumber(_game->player()->skillPoints());

    _image->loadFromSurface(_selectedImage);
    _image->setX(480);
    _image->setY(310);

    // Getting title and description by selected image
    std::map<std::string, Surface *>::iterator it;
    for(it = _images->begin(); it != _images->end(); ++it)
    {
        if (_selectedImage == it->second)
        {
            //std::string name = ;
            _title->setText(_titles->at(it->first).c_str());
        }
    }

}

void PlayerEditState::onButtonClick(Event * event)
{
    for (unsigned int i = 0; i != 18; ++i)
    {
        //std::cout << "SKILL "<< i << ": " << (int) _game->player()->skill(i) << std::endl;
    }

    std::map<std::string, ImageButton *>::iterator it;
    for(it = _buttons->begin(); it != _buttons->end(); ++it)
    {
        if (it->second == event->sender())
        {
            std::string name = it->first;

            if (name.find("stats_") == 0)
            {
                _selectedLabel = _labels->at(name.substr(0,7));
                _selectedImage = _images->at(name.substr(0,7));
                unsigned int number = atoi(name.substr(6,1).c_str());
                if (name.find("_increase") == 7)
                {
                    _game->player()->statsIncrease(number - 1);
                }
                else
                {
                    _game->player()->statsDecrease(number - 1);
                }
            }

            if (name.find("traits_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                _selectedLabel = _labels->at(name);
                _selectedImage = _images->at(name);
                _game->player()->traitToggle(number - 1);
            }

            if (name.find("skills_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                _selectedLabel = _labels->at(name);
                _selectedImage = _images->at(name);
                _game->player()->skillToggle(number - 1);
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
            _selectedImage = _images->at(it->first);
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
            if (name.find("stats_") == 0)
            {
                _selectedLabel = _labels->at(name);
                _selectedImage = _images->at(name);
            }
        }
    }
}

}
