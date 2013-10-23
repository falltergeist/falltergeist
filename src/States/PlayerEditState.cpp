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

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../States/PlayerEditState.h"
#include "../States/PlayerEditAgeState.h"
#include "../States/PlayerEditGenderState.h"
#include "../States/PlayerEditNameState.h"
#include "../States/PlayerEditAlertState.h"
#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/Player.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"

// Third party includes
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{

PlayerEditState::PlayerEditState(Game * game) : State(game)
{
    _labels       = new std::map<std::string, TextArea *>;
    _counters     = new std::map<std::string, BigCounter *>;
    _buttons      = new std::map<std::string, ImageButton *>;
    _masks        = new std::map<std::string, HiddenMask *>;
    _titles       = new std::map<std::string, std::string>;
    _descriptions = new std::map<std::string, std::string>;
    _images       = new std::map<std::string, Surface *>;

    // STATS
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/stat.msg");
        std::string images[] = { "strength", "perceptn", "endur", "charisma", "intel", "agility", "luck"};
        for (unsigned int i = 0; i != 7; ++i)
        {
            std::stringstream ss;
            ss << "stats_" << (i+1);

            _addTitle(ss.str(), msg->message(100 + i)->text());       // stat title
            _addDescription(ss.str(), msg->message(200 + i)->text()); // stat description
            _addImage(ss.str(), _game->resourceManager()->surface("art/skilldex/" + images[i] + ".frm")); // stat image
            _addLabel(ss.str(), new TextArea(102, 46 + 33*i));          // stat value label
            _addCounter(ss.str(), new BigCounter(59, 37 + 33*i));       // stat value counter
            _addMask(ss.str(), new HiddenMask(133, 29, 14, 36 + 33*i)); // stat click mask
            _addButton(ss.str() + "_increase", new ImageButton(ImageButton::BUTTON_PLUS,  149, 38 + 33*i)); // stat increase button
            _addButton(ss.str() + "_decrease", new ImageButton(ImageButton::BUTTON_MINUS, 149, 49 + 33*i)); // stat decrease button
        }

        _addCounter("statsPoints", new BigCounter(126, 282)); // Free stats points counter
    }

    // TRAITS
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/trait.msg");
        std::string images[] = { "fastmeta", "bruiser", "smlframe", "onehand", "finesse", "kamikaze", "heavyhnd", "fastshot",
                                  "bldmess", "jinxed", "goodnatr", "addict", "drugrest", "empathy", "skilled", "gifted"};

        for (unsigned int i = 0; i != 16; ++i)
        {
            std::stringstream ss;
            ss << "traits_" << (i+1);
            _addTitle(ss.str(), msg->message(100 + i)->text()); // trait title
            _addDescription(ss.str(), msg->message(200 + i)->text()); // trait description
            _addImage(ss.str(), _game->resourceManager()->surface("art/skilldex/" + images[i] + ".frm")); // trait image
            // left column
            if (i <= 7)
            {
                _addLabel(ss.str(),  new TextArea(msg->message(100 + i), 48, 353 + 13*i)); // trate label
                _addButton(ss.str(),  new ImageButton(ImageButton::BUTTON_SKILL_TOGGLE, 23,  352 + 13*i)); // trate toggle button
            }
            //right column
            else
            {
                _addLabel(ss.str(),  new TextArea(msg->message(100 + i), 169, 353 + 13*(i-8)))->setWidth(122)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT); // trate label
                _addButton(ss.str(),  new ImageButton(ImageButton::BUTTON_SKILL_TOGGLE, 299, 352 + 13*(i-8))); // trate toggle button
            }
        }
    }

    // SKILLS
    {
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/skill.msg");
        std::string images[] = { "gunsml", "gunbig", "energywp", "unarmed", "melee", "throwing", "firstaid", "doctor", "sneak",
                                 "lockpick", "steal", "traps", "science", "repair", "speech", "barter", "gambling", "outdoors"};
        for (unsigned int i = 0; i != 18; ++i)
        {
            std::stringstream ss;
            ss << "skills_" << (i+1);
            _addTitle(ss.str(), msg->message(100 + i)->text());
            _addDescription(ss.str(), msg->message(200 + i)->text());
            _addImage(ss.str(), _game->resourceManager()->surface("art/skilldex/" + images[i] + ".frm"));
            _addButton(ss.str(),  new ImageButton(ImageButton::BUTTON_SKILL_TOGGLE, 347,  26 + 11*i));
            _addLabel(ss.str(),  new TextArea(msg->message(100 + i), 377, 27 + 11*i))->setWidth(240);
            _addLabel(ss.str() + "_value",  new TextArea("", 577, 27 + 11*i));
        }
        // Free skill points counts
        _addCounter("skillsPoints", new BigCounter(522, 228));
    }

    // HEALTH CONDITION
    {
        std::string images[] = { "hitpoint", "poisoned", "radiated", "eyedamag", "armright", "armleft", "legright", "legleft"};
        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
        _addTitle("health_1", msg->message(300)->text());
        _addLabel("health_1",  new TextArea(msg->message(300), 194, 46)); //health
        _addDescription("health_1", _game->resourceManager()->msgFileType("text/english/game/stat.msg")->message(207)->text());
        _addImage("health_1", _game->resourceManager()->surface("art/skilldex/" + images[0] + ".frm"));

        for (unsigned int i = 0; i != 7; ++i)
        {
            std::stringstream ss;
            ss << "health_" << (i+2);
            _addTitle(ss.str(), msg->message(312 + i)->text());
            _addDescription(ss.str(), msg->message(400 + i)->text());
            _addLabel(ss.str(),  new TextArea(msg->message(312+i), 194, 46 + 13*(i+1)))->setColor(0xFF183018);
            _addImage(ss.str(), _game->resourceManager()->surface("art/skilldex/" + images[i+1] + ".frm"));
        }
    }

    // PLAYER PARAMS
    {
        std::string images[] = {"armorcls", "actionpt", "carryamt", "meleedam", "damresis", "poisnres", "radresis", "sequence", "healrate", "critchnc"};
        unsigned int labels[] = {302, 301, 311, 304, 305, 306, 307, 308, 309, 310};
        libfalltergeist::MsgFileType * msgStat = _game->resourceManager()->msgFileType("text/english/game/stat.msg");
        libfalltergeist::MsgFileType * msgEditor = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
        const int params[] = {109, 108, 112, 111, 124, 132, 131, 113, 114, 115};
        for (unsigned int i = 0; i != 10; ++i)
        {
            std::stringstream ss;
            ss << "params_" << (i+1);
            _addTitle(ss.str(), msgStat->message(params[i])->text());
            _addDescription(ss.str(), msgStat->message(params[i] + 100)->text());
            _addImage(ss.str(), _game->resourceManager()->surface("art/skilldex/" + images[i] + ".frm"));
            _addLabel(ss.str(),  new TextArea(msgEditor->message(labels[i]), 194, 182 + 13*i));
            _addLabel(ss.str() + "_value",  new TextArea("", 288, 182 + 13*i));
        }
    }


    Surface * background = new Surface(_game->resourceManager()->surface("art/intrface/edtrcrte.frm"));
    background->setX(0);
    background->setY(0);
    background->setXOffset(0);
    background->setYOffset(0);

    // description horizontal line
    for (unsigned int y = 300; y != 302; ++y) for (unsigned int x = 350; x != 620; ++x) background->setPixel(x,y, 0xFF000000);
    {
        _addButton("options", new ImageButton(ImageButton::BUTTON_SMALL_RED_CIRCLE, 345, 454));
        _addButton("done",    new ImageButton(ImageButton::BUTTON_SMALL_RED_CIRCLE, 455, 454));
        _addButton("cancel",  new ImageButton(ImageButton::BUTTON_SMALL_RED_CIRCLE, 554, 454));

        libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
        _addLabel("options", new TextArea(msg->message(101), 365, 453))->setColor(0xffb89c28)->setFont("font3.aaf");
        _addLabel("next",    new TextArea(msg->message(100), 473, 453))->setColor(0xffb89c28)->setFont("font3.aaf");
        _addLabel("cancel",  new TextArea(msg->message(102), 571, 453))->setColor(0xffb89c28)->setFont("font3.aaf");
        _addLabel("name",    new TextArea(_game->player()->name(), 17, 7))->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER)->setColor(0xffb89c28)->setFont("font3.aaf");
        _addLabel("age",     new TextArea("AGE", 163, 7))->setColor(0xffb89c28)->setFont("font3.aaf");
        _addLabel("gender",  new TextArea(msg->message(_game->player()->gender() == Player::GENDER_MALE ? 107 : 108), 255, 7))->setColor(0xffb89c28)->setFont("font3.aaf");
        _addLabel("label_1", new TextArea(msg->message(112), 18, 286))->setColor(0xffb89c28)->setFont("font3.aaf"); // ДОП. ОЧКИ
        _addLabel("label_2", new TextArea(msg->message(139), 50, 326))->setColor(0xffb89c28)->setFont("font3.aaf"); // ДОП. ОСОБЕННОСТИ
        _addLabel("label_3", new TextArea(msg->message(117), 383, 5))->setColor(0xffb89c28)->setFont("font3.aaf");  // НАВЫКИ
        _addLabel("label_4", new TextArea(msg->message(138), 428, 233))->setColor(0xffb89c28)->setFont("font3.aaf"); // ОСНОВН.
        _addTitle("label_1", msg->message(120)->text());
        _addTitle("label_2", msg->message(146)->text());
        _addTitle("label_3", msg->message(150)->text());
        _addTitle("label_4", msg->message(144)->text());
        _addDescription("label_1", msg->message(121)->text());
        _addDescription("label_2", msg->message(147)->text());
        _addDescription("label_3", msg->message(151)->text());
        _addDescription("label_4", msg->message(145)->text());
        _addImage("label_1", new Surface(_game->resourceManager()->surface("art/skilldex/generic.frm")));
        _addImage("label_2", new Surface(_game->resourceManager()->surface("art/skilldex/traits.frm")));
        _addImage("label_3", new Surface(_game->resourceManager()->surface("art/skilldex/skills.frm")));
        _addImage("label_4", new Surface(_game->resourceManager()->surface("art/skilldex/skills.frm")));

    }
    // Name change button
    {
        const char * on  = "art/intrface/nameon.frm";
        const char * off = "art/intrface/nameoff.frm";
        _addButton("name",  new ImageButton(off, on, 13, 0));
    }
    // Age change button
    {
        const char * on  = "art/intrface/ageon.frm";
        const char * off = "art/intrface/ageoff.frm";
        _addButton("age",  new ImageButton(off, on, 156, 0));
    }
    //Gender change button
    {
        const char * on  = "art/intrface/sexon.frm";
        const char * off = "art/intrface/sexoff.frm";
        _addButton("gender",  new ImageButton(off, on, 236, 0));
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
            //it->second->setBorderColor(0xFFFF0000);
            it->second->setVisible(true);
            it->second->onLeftButtonClick((EventHandler) &PlayerEditState::onMaskClick);
            add(it->second);
        }
    }

    _selectedImage = _images->at("stats_1");
    _selectedLabel = _labels->at("stats_1");
    _image = new Surface(_selectedImage);
    add(_image);

    _title = new TextArea("", 350,275);
    _title->setFont("font2.aaf")->setColor(0xFF000000);
    add(_title);

    _description = new TextArea("", 350, 315);
    _description->setColor(0xFF000000)->setWidth(145)->setHeight(120)->setWordWrap(true);
    add(_description);

}

PlayerEditState::~PlayerEditState()
{
    delete _labels;
    delete _buttons;
    delete _counters;
    delete _masks;

    delete _titles;
    delete _descriptions;

    //std::map<std::string, Surface *>::iterator it;
    //for (it = _images->begin(); it != _images->end(); ++it) delete it->second;
    delete _images;
}

void PlayerEditState::init()
{
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
    Player * player = _game->player();
    libfalltergeist::MsgFileType * msgEditor = _game->resourceManager()->msgFileType("text/english/game/editor.msg");

    _labels->at("name")->setText(player->name());
    _labels->at("age")->setText(msgEditor->message(104))->appendText(" ")->appendText(player->age());
    _labels->at("gender")->setText(msgEditor->message(player->gender() == Player::GENDER_MALE ? 107 : 108));

    _counters->at("statsPoints")->setNumber(player->characterPoints());
    _counters->at("skillsPoints")->setNumber(player->skillPoints());

    _labels->at("health_1")->setText(msgEditor->message(300))->appendText("  ")->appendText(player->hitPointsMaximum())->appendText("/")->appendText(player->hitPointsMaximum());
    _labels->at("params_1_value")->setText(player->armorClass());
    _labels->at("params_2_value")->setText(player->actionPoints());
    _labels->at("params_3_value")->setText(player->carryWeight());
    _labels->at("params_4_value")->setText(player->meleeDamage());
    _labels->at("params_5_value")->setText(player->damageResistance())->appendText("%");
    _labels->at("params_6_value")->setText(player->poisonResistance())->appendText("%");
    _labels->at("params_7_value")->setText(player->radiationResistance())->appendText("%");
    _labels->at("params_8_value")->setText(player->sequence());
    _labels->at("params_9_value")->setText(player->healingRate());
    _labels->at("params_10_value")->setText(player->criticalChance())->appendText("%");

    // Stats counters and labels
    for (unsigned int i = 0; i != 7; ++i)
    {
        std::stringstream ss;
        ss << "stats_" << (i+1);
        unsigned int val = player->stat(i) + player->statBonus(i);
        _counters->at(ss.str())->setNumber(val);
        _counters->at(ss.str())->setColor(BigCounter::COLOR_WHITE);
        if (val > 10)
        {
            val = 10;
            _counters->at(ss.str())->setColor(BigCounter::COLOR_RED);
        }
        _labels->at(ss.str())->setText(msgEditor->message(199 + (val < 1 ? 1 : val)));
    }

    // Skills values
    for (unsigned int i = 0; i != 18; ++i)
    {
        std::stringstream ss;
        ss << "skills_" << (i + 1) << "_value";
        _labels->at(ss.str())->setText(player->skillValue(i))->appendText("%");
    }


    std::map<std::string, TextArea *>::iterator it;
    // Default labels colors
    for(it = _labels->begin(); it != _labels->end(); ++it)
    {
        std::string name = it->first;


        if (name.find("stats_") == 0 || name.find("params_") == 0)
        {
            it->second->setColor(0xFF3FF800);
        }

        if (name.find("traits_") == 0)
        {
            unsigned int number = atoi(name.substr(7).c_str());
            it->second->setColor(player->trait(number - 1) ? 0xFFA0A0A0 : 0xFF3FF800);
        }

        if (name.find("skills_") == 0)
        {
            unsigned int number = atoi(name.substr(7).c_str());
            it->second->setColor(player->skill(number - 1) ? 0xFFA0A0A0 : 0xFF3FF800);
        }

        if (name.find("health_") == 0)
        {
            it->second->setColor(name.compare("health_1") == 0 ? 0xFF3FF800 : 0xFF183018);
        }
    }

    // Selected labels colors
    for(it = _labels->begin(); it != _labels->end(); ++it)
    {
        if (_selectedLabel != it->second) continue;

        std::string name = it->first;

        _title->setText(_titles->at(name));
        _description->setText(_descriptions->at(name));
        _selectedImage = _images->at(name);
        _image->loadFromSurface(_selectedImage);
        _image->setX(480);
        _image->setY(310);
        _image->setXOffset(0);
        _image->setYOffset(0);

        if (name.find("stats_") == 0)
        {
            it->second->setColor(0xFFFFFF7F);
        }

        if (name.find("params_") == 0)
        {
            it->second->setColor(0xFFFFFF7F);
            _labels->at(name+"_value")->setColor(0xFFFFFF7F);
        }

        if (name.find("traits_") == 0)
        {
            unsigned int number = atoi(name.substr(7).c_str());
            it->second->setColor(player->trait(number - 1) ? 0xFFFFFFFF : 0xFFFFFF7F);
        }

        if (name.find("skills_") == 0)
        {
            unsigned int number = atoi(name.substr(7).c_str());
            it->second->setColor(player->skill(number - 1) ? 0xFFFFFFFF : 0xFFFFFF7F);
            _labels->at(name+"_value")->setColor(player->skill(number - 1) ? 0xFFFFFFFF : 0xFFFFFF7F);
        }

        if (name.find("health_") == 0)
        {
            it->second->setColor(name.compare("health_1") == 0 ? 0xFFFFFF7F : 0xFF707820);
        }
    }

}

void PlayerEditState::onButtonClick(Event * event)
{    

    std::map<std::string, ImageButton *>::iterator it;
    for(it = _buttons->begin(); it != _buttons->end(); ++it)
    {
        if (it->second == event->sender())
        {
            std::string name = it->first;

            if (name.compare("name") == 0) return onNameButtonClick(event);
            if (name.compare("age") == 0) return onAgeButtonClick(event);
            if (name.compare("gender") == 0) return onGenderButtonClick(event);
            if (name.compare("cancel") == 0) return onBackButtonClick(event);
            if (name.compare("done") == 0) return onDoneButtonClick(event);

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
                if (!_game->player()->traitToggle(number - 1))
                {
                    PlayerEditAlertState * state = new PlayerEditAlertState(_game);
                    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
                    std::string text = msg->message(148)->text();
                    text += "\n";
                    text += msg->message(149)->text();
                    state->setMessage(text);
                    _game->pushState(state);
                }
            }

            if (name.find("skills_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                _selectedLabel = _labels->at(name);
                _selectedImage = _images->at(name);
                if (!_game->player()->skillToggle(number - 1))
                {
                    PlayerEditAlertState * state = new PlayerEditAlertState(_game);
                    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
                    std::string text = msg->message(140)->text();
                    text += "\n";
                    text += msg->message(141)->text();
                    state->setMessage(text);
                    _game->pushState(state);
                }
            }
        }
    }
}

void PlayerEditState::onLabelClick(Event * event)
{
    std::map<std::string, TextArea *>::iterator it;
    for(it = _labels->begin(); it != _labels->end(); ++it)
    {
        std::string name = it->first;
        if (it->second == event->sender())
        {
            if (name.find("stats_") == 0 || name.find("traits_") == 0 || name.find("skills_") == 0 || name.find("health_") == 0 || name.find("params_") == 0 || name.find("label_") == 0)
            {
                std::string label = name;
                if (name.find("_value") > 0)
                {
                    label = name.substr(0, name.find("_value"));
                }
                _selectedLabel = _labels->at(label.c_str());
                _selectedImage = _images->at(label.c_str());
            }
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


void PlayerEditState::onNameButtonClick(Event * event)
{
    _game->pushState(new PlayerEditNameState(_game));
}

void PlayerEditState::onAgeButtonClick(Event * event)
{
    _game->pushState(new PlayerEditAgeState(_game));
}

void PlayerEditState::onGenderButtonClick(Event * event)
{
    _game->pushState(new PlayerEditGenderState(_game));
}

void PlayerEditState::onBackButtonClick(Event *event)
{
    _game->popState();
}

void PlayerEditState::onDoneButtonClick(Event * event)
{
    _game->setState(new LocationState(_game));
}

}
