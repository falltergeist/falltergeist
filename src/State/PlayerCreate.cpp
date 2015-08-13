/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include "../Font.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../State/PlayerEditAge.h"
#include "../State/PlayerEditAlert.h"
#include "../State/PlayerEditGender.h"
#include "../State/PlayerEditName.h"
#include "../State/PlayerCreateOptions.h"
#include "../State/PlayerCreate.h"
#include "../UI/Image.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{
namespace State
{

PlayerCreate::PlayerCreate() : State()
{
}

PlayerCreate::~PlayerCreate()
{
}

void PlayerCreate::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(true);
    setModal(true);

    // background
    auto background = new Image("art/intrface/edtrcrte.frm");
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);
    addUI(background);

    // STATS
    std::string imagesStats[] = { "strength", "perceptn", "endur", "charisma", "intel", "agility", "luck"};
    for (unsigned int i = 0; i != 7; ++i)
    {
        std::stringstream ss;
        ss << "stats_" << (i+1);

        _addTitle(ss.str(), _t(MSG_STATS, 100 + i));       // stat title
        _addDescription(ss.str(), _t(MSG_STATS, 200 + i)); // stat description
        _addImage(ss.str(), new Image("art/skilldex/" + imagesStats[i] + ".frm")); // stat image
        _addLabel(ss.str(), new TextArea(backgroundX+104, backgroundY+46+33*i));          // stat value label
        _addCounter(ss.str(), new BigCounter(backgroundX+59, backgroundY+37+33*i));       // stat value counter
        _addMask(ss.str(), new HiddenMask(133, 29, backgroundX+14, backgroundY+36+33*i)); // stat click mask
        _addButton(ss.str() + "_increase", new ImageButton(ImageButton::TYPE_PLUS,  backgroundX+149, backgroundY+38+33*i)); // stat increase button
        _addButton(ss.str() + "_decrease", new ImageButton(ImageButton::TYPE_MINUS, backgroundX+149, backgroundY+49+33*i)); // stat decrease button
    }

    _addCounter("statsPoints", new BigCounter(backgroundX+126, backgroundY+282)); // Free stats points counter

    // TRAITS
    std::string imagesTraits[] =  { "fastmeta", "bruiser", "smlframe", "onehand", "finesse",  "kamikaze", "heavyhnd", "fastshot",
                                    "bldmess",  "jinxed",  "goodnatr", "addict",  "drugrest", "empathy", "skilled",   "gifted" };
    for (unsigned int i = 0; i != 16; ++i)
    {
        std::stringstream ss;
        ss << "traits_" << (i+1);
        _addTitle(ss.str(), _t(MSG_TRAITS, 100 + i)); // trait title
        _addDescription(ss.str(), _t(MSG_TRAITS, 200 + i)); // trait description
        _addImage(ss.str(), new Image("art/skilldex/" + imagesTraits[i] + ".frm")); // trait image
        // left column
        if (i <= 7)
        {
            _addLabel(ss.str(),  new TextArea(_t(MSG_TRAITS, 100 + i), backgroundX+48, backgroundY+353+13*i)); // trate label
            _addButton(ss.str(), new ImageButton(ImageButton::TYPE_SKILL_TOGGLE, backgroundX+23, backgroundY+352+13*i)); // trate toggle button
        }
        //right column
        else
        {
            auto label = new TextArea(_t(MSG_TRAITS, 100 + i), backgroundX+169, backgroundY+353+13*(i-8));
            label->setWidth(122);
            label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
            _addLabel(ss.str(),  label); // trate label
            _addButton(ss.str(), new ImageButton(ImageButton::TYPE_SKILL_TOGGLE, backgroundX+299, backgroundY+352+13*(i-8))); // trate toggle button
        }
    }

    // SKILLS
    std::string imagesSkills[]  = { "gunsml",   "gunbig", "energywp", "unarmed", "melee",  "throwing", "firstaid", "doctor",   "sneak",
                                    "lockpick", "steal",  "traps",    "science", "repair", "speech",   "barter",   "gambling", "outdoors"};
    for (unsigned int i = 0; i != 18; ++i)
    {
        std::stringstream ss;
        ss << "skills_" << (i+1);
        _addTitle(ss.str(), _t(MSG_SKILLS, 100 + i));
        _addDescription(ss.str(), _t(MSG_SKILLS, 200 + i));
        _addImage(ss.str(), new Image("art/skilldex/" + imagesSkills[i] + ".frm"));
        _addButton(ss.str(), new ImageButton(ImageButton::TYPE_SKILL_TOGGLE, backgroundX+347, backgroundY+26+11*i));
        _addLabel(ss.str(),  new TextArea(_t(MSG_SKILLS, 100 + i), backgroundX+377, backgroundY+27+11*i))->setWidth(240);
        _addLabel(ss.str() + "_value",  new TextArea("", backgroundX+577, backgroundY+27+11*i));
    }
    // Free skill points counts
    _addCounter("skillsPoints", new BigCounter(backgroundX+522, backgroundY+228));

    // HEALTH CONDITION
    std::string imagesHealth[] = { "hitpoint", "poisoned", "radiated", "eyedamag", "armright", "armleft", "legright", "legleft"};
    _addTitle("health_1", _t(MSG_EDITOR, 300));
    _addLabel("health_1",  new TextArea(_t(MSG_EDITOR, 300), backgroundX+194, backgroundY+46)); //health
    _addDescription("health_1", _t(MSG_STATS, 207));
    _addImage("health_1", new Image("art/skilldex/" + imagesHealth[0] + ".frm"));

    auto font1_0x183018ff = ResourceManager::getInstance()->font("font1.aaf", 0x183018ff);

    for (unsigned int i = 0; i != 7; ++i)
    {
        std::stringstream ss;
        ss << "health_" << (i+2);
        _addTitle(ss.str(), _t(MSG_EDITOR, 312 + i));
        _addDescription(ss.str(), _t(MSG_EDITOR, 400 + i));
        _addLabel(ss.str(), new TextArea(_t(MSG_EDITOR, 312 + i), backgroundX+194, backgroundY+46+13*(i+1)))->setFont(font1_0x183018ff);
        _addImage(ss.str(), new Image("art/skilldex/" + imagesHealth[i+1] + ".frm"));
    }

    // PLAYER PARAMS
    std::string imagesParams[] = {"armorcls", "actionpt", "carryamt", "meleedam", "damresis", "poisnres", "radresis", "sequence", "healrate", "critchnc"};
    unsigned int labels[] = {302, 301, 311, 304, 305, 306, 307, 308, 309, 310};
    const int params[] = {109, 108, 112, 111, 124, 132, 131, 113, 114, 115};
    for (unsigned int i = 0; i != 10; ++i)
    {
        std::stringstream ss;
        ss << "params_" << (i+1);
        _addTitle(ss.str(), _t(MSG_STATS, params[i]));
        _addDescription(ss.str(), _t(MSG_STATS, params[i] + 100));
        _addImage(ss.str(), new Image("art/skilldex/" + imagesParams[i] + ".frm"));
        _addLabel(ss.str(), new TextArea(_t(MSG_EDITOR, labels[i]), backgroundX + 194, backgroundY + 179 + 13*i));
        _addLabel(ss.str() + "_value", new TextArea("", backgroundX + 288, backgroundY + 179 + 13*i));
    }

    _addButton("options", new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+345, backgroundY+454));
    _addButton("done",    new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+455, backgroundY+454));
    _addButton("cancel",  new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+554, backgroundY+454));

    auto font3_b89c28ff = ResourceManager::getInstance()->font("font3.aaf", 0xb89c28ff);

    _addLabel("options", new TextArea(_t(MSG_EDITOR, 101), backgroundX+365, backgroundY+453))->setFont(font3_b89c28ff);
    _addLabel("next",    new TextArea(_t(MSG_EDITOR, 100), backgroundX+473, backgroundY+453))->setFont(font3_b89c28ff);
    _addLabel("cancel",  new TextArea(_t(MSG_EDITOR, 102), backgroundX+571, backgroundY+453))->setFont(font3_b89c28ff);
    auto label = _addLabel("name",    new TextArea(Game::getInstance()->player()->name(), backgroundX+17, backgroundY+7));
    label->setWidth(150);
    label->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    label->setFont(font3_b89c28ff);
    _addLabel("age",     new TextArea(_t(MSG_EDITOR, 104), backgroundX+163, backgroundY+7))->setFont(font3_b89c28ff);
    _addLabel("gender",  new TextArea(_t(MSG_EDITOR, Game::getInstance()->player()->gender() == GENDER::MALE ? 107 : 108), backgroundX+250, backgroundY+7))->setFont(font3_b89c28ff);
    _addLabel("label_1", new TextArea(_t(MSG_EDITOR, 116), backgroundX+14, backgroundY+286))->setFont(font3_b89c28ff);  // char points
    _addLabel("label_2", new TextArea(_t(MSG_EDITOR, 139), backgroundX+50, backgroundY+326))->setFont(font3_b89c28ff);  // optinal traits
    _addLabel("label_3", new TextArea(_t(MSG_EDITOR, 117), backgroundX+383, backgroundY+5))->setFont(font3_b89c28ff);   // skills
    _addLabel("label_4", new TextArea(_t(MSG_EDITOR, 138), backgroundX+428, backgroundY+233))->setFont(font3_b89c28ff); // tag skills
    _addTitle("label_1", _t(MSG_EDITOR, 120));
    _addTitle("label_2", _t(MSG_EDITOR, 146));
    _addTitle("label_3", _t(MSG_EDITOR, 150));
    _addTitle("label_4", _t(MSG_EDITOR, 144));
    _addDescription("label_1", _t(MSG_EDITOR, 121));
    _addDescription("label_2", _t(MSG_EDITOR, 147));
    _addDescription("label_3", _t(MSG_EDITOR, 151));
    _addDescription("label_4", _t(MSG_EDITOR, 145));
    _addImage("label_1", new Image("art/skilldex/generic.frm"));
    _addImage("label_2", new Image("art/skilldex/traits.frm"));
    _addImage("label_3", new Image("art/skilldex/skills.frm"));
    _addImage("label_4", new Image("art/skilldex/skills.frm"));

    // Name change button
    _addButton("name",  new ImageButton(ImageButton::TYPE_PLAYER_NAME, backgroundX+13, backgroundY+0));

    // Age change button
    _addButton("age", new ImageButton(ImageButton::TYPE_PLAYER_AGE, backgroundX+156, backgroundY+0));

    //Gender change button
    _addButton("gender", new ImageButton(ImageButton::TYPE_PLAYER_GENDER, backgroundX+236, backgroundY+0));

    // add buttons to the state
    for(auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        it->second->addEventHandler("mouseleftclick", [this](Event* event){ this->onButtonClick(dynamic_cast<MouseEvent*>(event)); });
        addUI(it->second);
    }

    // add labels to the state
    // reverse iterator to change drawing order
    for(auto it = _labels.rbegin(); it != _labels.rend(); ++it)
    {
        it->second->addEventHandler("mouseleftdown", [this](Event* event){ this->onLabelClick(dynamic_cast<MouseEvent*>(event)); });
        addUI(it->second);
    }

    // add counters to the state
    for(auto it = _counters.begin(); it != _counters.end(); ++it)
    {
        addUI(it->second);
    }

    // add hidden masks
    for(auto it = _masks.begin(); it != _masks.end(); ++it)
    {
        it->second->addEventHandler("mouseleftdown", [this](Event* event){ this->onMaskClick(dynamic_cast<MouseEvent*>(event)); });
        addUI(it->second);
    }

    _selectedImage = _images.at("stats_1");
    _selectedLabel = _labels.at("stats_1");
    _selectedImage->setX(backgroundX+480);
    _selectedImage->setY(backgroundY+310);
    addUI(_selectedImage);

    auto font1_000000ff = ResourceManager::getInstance()->font("font1.aaf", 0x000000FF);
    auto font2_000000ff = ResourceManager::getInstance()->font("font2.aaf", 0x000000FF);

    _title = new TextArea("", backgroundX+350, backgroundY+275);
    _title->setFont(font2_000000ff);
    addUI(_title);

    auto line = new Image(270, 2);
    line->setX(backgroundX+350);
    line->setY(backgroundY+300);
    line->texture()->fill(0x000000ff);
    addUI(line);

    _description = new TextArea("", backgroundX+350, backgroundY+315);
    _description->setFont(font1_000000ff);
    _description->setWidth(140);
    _description->setHeight(120);
    _description->setWordWrap(true);
    addUI(_description);
}

TextArea* PlayerCreate::_addLabel(const std::string& name, TextArea* label)
{
    _labels.insert(std::pair<std::string,TextArea*>(name, label));
    return label;
}

ImageButton* PlayerCreate::_addButton(const std::string& name, ImageButton* button)
{
    _buttons.insert(std::pair<std::string,ImageButton*>(name, button));
    return button;
}

BigCounter* PlayerCreate::_addCounter(const std::string& name, BigCounter* counter)
{
    _counters.insert(std::pair<std::string,BigCounter*>(name, counter));
    return counter;
}

HiddenMask* PlayerCreate::_addMask(const std::string& name, HiddenMask* mask)
{
    _masks.insert(std::pair<std::string,HiddenMask*>(name, mask));
    return mask;
}

void PlayerCreate::_addTitle(const std::string& name, std::string title)
{
    _titles.insert(std::pair<std::string,std::string>(name, title));
}

void PlayerCreate::_addDescription(const std::string& name, std::string description)
{
    _descriptions.insert(std::pair<std::string,std::string>(name, description));
}

void PlayerCreate::_addImage(const std::string& name, Image* image)
{
    _images.insert(std::pair<std::string, Image*>(name, image));
}


void PlayerCreate::think()
{
    State::think();
    auto player = Game::getInstance()->player();

    *_labels.at("name") = player->name();
    *_labels.at("age") = _t(MSG_EDITOR, 104) +  " " + std::to_string(player->age());

    *_labels.at("gender") = _t(MSG_EDITOR, player->gender() == GENDER::MALE ? 107 : 108);

    _counters.at("statsPoints")->setNumber(player->statsPoints());
    _counters.at("skillsPoints")->setNumber(player->skillsPoints());

    *_labels.at("health_1") = _t(MSG_EDITOR, 300) + "  " + std::to_string(player->hitPointsMax()) + "/" + std::to_string(player->hitPointsMax());
    *_labels.at("params_1_value") = player->armorClass();
    *_labels.at("params_2_value") = player->actionPoints();
    *_labels.at("params_3_value") = player->carryWeightMax();
    *_labels.at("params_4_value") = player->meleeDamage();

    *_labels.at("params_5_value") = player->damageResistance();
    *_labels.at("params_5_value")+= "%";

    *_labels.at("params_6_value") = player->poisonResistance();
    *_labels.at("params_6_value")+= "%";

    *_labels.at("params_7_value") = player->radiationResistance();
    *_labels.at("params_7_value")+= "%";

    *_labels.at("params_8_value") = player->sequence();
    *_labels.at("params_9_value") = player->healingRate();
    *_labels.at("params_10_value") = player->criticalChance();

    *_labels.at("params_10_value") += "%";

    // Stats counters and labels
    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
    {
        std::stringstream ss;
        ss << "stats_" << (i+1);
        unsigned int val = player->statTotal((STAT)i);
        _counters.at(ss.str())->setNumber(val);
        _counters.at(ss.str())->setColor(BigCounter::COLOR_WHITE);
        if (val > 10)
        {
            val = 10;
            _counters.at(ss.str())->setColor(BigCounter::COLOR_RED);
        }
        _labels.at(ss.str())->setText(_t(MSG_EDITOR, 199 + (val < 1 ? 1 : val)));
    }

    // Skills values
    for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
    {
        std::stringstream ss;
        ss << "skills_" << (i + 1) << "_value";
        *_labels.at(ss.str()) = player->skillValue((SKILL)i);
        *_labels.at(ss.str())+= "%";
    }

    // Default labels colors
    for(auto it = _labels.begin(); it != _labels.end(); ++it)
    {
        std::string name = it->first;

        auto font1_3ff800ff = ResourceManager::getInstance()->font("font1.aaf", 0x3ff800ff);
        auto font1_a0a0a0ff = ResourceManager::getInstance()->font("font1.aaf", 0xa0a0a0ff);
        auto font1_183018ff = ResourceManager::getInstance()->font("font1.aaf", 0x183018ff);

        if (name.find("stats_") == 0 || name.find("params_") == 0)
        {
            it->second->setFont(font1_3ff800ff);
        }

        if (name.find("traits_") == 0)
        {
            unsigned number = atoi(name.substr(7).c_str()) - 1;
            it->second->setFont(player->traitTagged((TRAIT)number) ? font1_a0a0a0ff : font1_3ff800ff);
        }

        if (name.find("skills_") == 0)
        {
            unsigned number = atoi(name.substr(7).c_str()) - 1;
            it->second->setFont(player->skillTagged((SKILL)number) ? font1_a0a0a0ff : font1_3ff800ff);
        }

        if (name.find("health_") == 0)
        {
            it->second->setFont(name.compare("health_1") == 0 ? font1_3ff800ff : font1_183018ff);
        }
    }

    // Selected labels colors
    for(auto it = _labels.begin(); it != _labels.end(); ++it)
    {
        if (_selectedLabel != it->second) continue;

        std::string name = it->first;

        _title->setText(_titles.at(name));
        _description->setText(_descriptions.at(name));
        _selectedImage->setTexture(_images.at(name)->texture());

        auto font1_ffff7fff = ResourceManager::getInstance()->font("font1.aaf", 0xffff7fff);
        auto font1_ffffffff = ResourceManager::getInstance()->font("font1.aaf", 0xffffffff);
        auto font1_707820ff = ResourceManager::getInstance()->font("font1.aaf", 0x707820ff);

        if (name.find("stats_") == 0)
        {
            it->second->setFont(font1_ffff7fff);
        }

        if (name.find("params_") == 0)
        {
            it->second->setFont(font1_ffff7fff);
            _labels.at(name+"_value")->setFont(font1_ffff7fff);
        }

        if (name.find("traits_") == 0)
        {
            unsigned number = atoi(name.substr(7).c_str()) - 1;
            it->second->setFont(player->traitTagged((TRAIT)number) ? font1_ffffffff : font1_ffff7fff);
        }

        if (name.find("skills_") == 0)
        {
            unsigned number = atoi(name.substr(7).c_str()) - 1;
            it->second->setFont(player->skillTagged((SKILL)number) ? font1_ffffffff : font1_ffff7fff);
            _labels.at(name+"_value")->setFont(player->skillTagged((SKILL)number) ? font1_ffffffff : font1_ffff7fff);
        }

        if (name.find("health_") == 0)
        {
            it->second->setFont(name.compare("health_1") == 0 ? font1_ffff7fff : font1_707820ff);
        }
    }

}

bool PlayerCreate::_statDecrease(unsigned int num)
{
    auto player = Game::getInstance()->player();
    if (player->stat((STAT)num) <= 1) return false;

    player->setStat((STAT)num, player->stat((STAT)num) - 1);
    player->setStatsPoints(player->statsPoints() + 1);
    return true;
}

bool PlayerCreate::_statIncrease(unsigned int num)
{
    auto player = Game::getInstance()->player();
    if (player->statsPoints() <= 0) return false;

    if (player->stat((STAT)num) + player->statBonus((STAT)num) >= 10) return false;

    player->setStat((STAT)num, player->stat((STAT)num) + 1);
    player->setStatsPoints(player->statsPoints() - 1);
    return true;
}

bool PlayerCreate::_traitToggle(unsigned int num)
{
    auto player = Game::getInstance()->player();
    if (player->traitTagged((TRAIT)num))
    {
        player->setTraitTagged((TRAIT)num, 0);
        return true;
    }
    else
    {
        unsigned int selectedTraits = 0;
        for (unsigned i = (unsigned)TRAIT::FAST_METABOLISM; i <= (unsigned)TRAIT::GIFTED; i++)
        {
            if (player->traitTagged((TRAIT)i)) selectedTraits++;
        }
        if (selectedTraits < 2)
        {
            player->setTraitTagged((TRAIT)num, 1);
            return true;
        }
    }
    return false;
}

bool PlayerCreate::_skillToggle(unsigned int num)
{
    auto player = Game::getInstance()->player();
    if (player->skillTagged((SKILL)num))
    {
        player->setSkillTagged((SKILL)num, 0);
        player->setSkillsPoints(player->skillsPoints() + 1);
        return true;
    }
    else
    {
        if (player->skillsPoints() > 0)
        {
            player->setSkillTagged((SKILL)num, 1);
            player->setSkillsPoints(player->skillsPoints() - 1);
            return true;
        }
    }
    return false;
}

void PlayerCreate::onButtonClick(MouseEvent* event)
{
    auto sender = dynamic_cast<ImageButton*>(event->emitter());

    for(auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        if (it->second == sender)
        {
            std::string name = it->first;

            if (name == "name") return onNameButtonClick(event);
            if (name == "age")  return onAgeButtonClick(event);
            if (name == "gender") return onGenderButtonClick(event);
            if (name == "cancel") return onBackButtonClick(event);
            if (name == "done") return onDoneButtonClick(event);
            if (name == "options") return onOptionsButtonClick(event);

            if (name.find("stats_") == 0)
            {
                _selectedLabel = _labels.at(name.substr(0,7));
                _selectedImage->setTexture(_images.at(name.substr(0,7))->texture());
                unsigned int number = atoi(name.substr(6,1).c_str());
                if (name.find("_increase") == 7)
                {
                    _statIncrease(number - 1);
                }
                else
                {
                    _statDecrease(number - 1);
                }
            }

            if (name.find("traits_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                _selectedLabel = _labels.at(name);
                _selectedImage->setTexture(_images.at(name)->texture());

                if (!_traitToggle(number - 1))
                {
                    auto state = new PlayerEditAlert();
                    state->setMessage(_t(MSG_EDITOR, 148) + "\n" + _t(MSG_EDITOR, 149));
                    Game::getInstance()->pushState(state);
                }
            }

            if (name.find("skills_") == 0)
            {
                unsigned int number = atoi(name.substr(7).c_str());
                _selectedLabel = _labels.at(name);
                _selectedImage->setTexture(_images.at(name)->texture());
                if (!_skillToggle(number - 1))
                {
                    auto state = new PlayerEditAlert();
                    state->setMessage(_t(MSG_EDITOR, 140) + "\n" + _t(MSG_EDITOR, 141));
                    Game::getInstance()->pushState(state);
                }
            }
        }
    }
}

void PlayerCreate::onLabelClick(MouseEvent* event)
{
    for(auto it = _labels.begin(); it != _labels.end(); ++it)
    {
        std::string name = it->first;
        if (it->second == event->emitter())
        {
            if (name.find("stats_") == 0 || name.find("traits_") == 0 || name.find("skills_") == 0 || name.find("health_") == 0 || name.find("params_") == 0 || name.find("label_") == 0)
            {
                std::string label = name;
                if (name.find("_value") > 0)
                {
                    label = name.substr(0, name.find("_value"));
                }
                _selectedLabel = _labels.at(label.c_str());
                _selectedImage->setTexture(_images.at(label.c_str())->texture());
            }
        }
    }
}

void PlayerCreate::onMaskClick(MouseEvent* event)
{
    for(auto it = _masks.begin(); it != _masks.end(); ++it)
    {
        if (it->second == event->emitter())
        {
            std::string name = it->first;
            if (name.find("stats_") == 0)
            {
                _selectedLabel = _labels.at(name);
                _selectedImage->setTexture(_images.at(name)->texture());
            }
        }
    }
}


void PlayerCreate::onNameButtonClick(MouseEvent* event)
{
    doName();
}

void PlayerCreate::onAgeButtonClick(MouseEvent* event)
{
    doAge();
}

void PlayerCreate::onGenderButtonClick(MouseEvent* event)
{
    doGender();
}

void PlayerCreate::onBackButtonClick(MouseEvent* event)
{
    doBack();
}

void PlayerCreate::onDoneButtonClick(MouseEvent* event)
{
    doDone();
}

void PlayerCreate::onOptionsButtonClick(MouseEvent* event)
{
    doOptions();
}

void PlayerCreate::doAge()
{
    Game::getInstance()->pushState(new PlayerEditAge());
}

void PlayerCreate::doBack()
{
    Game::getInstance()->popState();
}

void PlayerCreate::doDone()
{
    auto player = Game::getInstance()->player();
    player->setHitPoints(player->hitPointsMax());
    Game::getInstance()->setState(new Location());
}

void PlayerCreate::doGender()
{
    Game::getInstance()->pushState(new PlayerEditGender());
}

void PlayerCreate::doName()
{
    Game::getInstance()->pushState(new PlayerEditName());
}

void PlayerCreate::doOptions()
{
    Game::getInstance()->pushState(new PlayerCreateOptions());
}

void PlayerCreate::onKeyDown(KeyboardEvent* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_c:
            doBack();
            break;
        case SDLK_RETURN:
        case SDLK_d:
            doDone();
            break;
        case SDLK_o:
            doOptions();
            break;
        case SDLK_a:
            doAge();
            break;
        case SDLK_s:
            doGender();
            break;
        case SDLK_n:
            doName();
            break;
    }
}

}
}
