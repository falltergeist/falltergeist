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
#include <iostream>

// Falltergeist includes
#include "../Font.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../State/PlayerEditAlert.h"
#include "../State/PlayerEdit.h"
#include "../UI/Image.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{
namespace State
{

PlayerEdit::PlayerEdit() : State()
{
}

PlayerEdit::~PlayerEdit()
{
}

void PlayerEdit::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    auto player = Game::getInstance()->player();

    // background
    auto background = new Image("art/intrface/edtredt.frm");
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
    }

    // LEVEL window
    auto level = player->level();
    int expNext = level*(level+1)*500; // experience needed for next level
    std::string imagesLevel[] = { "level", "exper", "levelnxt"};
    for (unsigned int i = 0; i != 3; ++i)
    {
        std::stringstream ss;
        std::stringstream tmp;
        std::string line = "";
        ss << "level_" << (i+1);
        // Level 401 stat, Experience 402 stat, Next level 122 editor
        switch (i)
        {
            case 0:
                line = _t(MSG_STATS, 401);
                break;
            case 1:
                line = _t(MSG_STATS, 402);
                break;
            case 2:
                line = _t(MSG_EDITOR, 122);
                break;
        }
        _addTitle(ss.str(), line);
        // description: level: 501 stat, exp: 502 stat, levelnxt: editor 123
        switch (i)
        {
            case 0:
                line = _t(MSG_STATS, 501);
                break;
            case 1:
                line = _t(MSG_STATS, 502);
                break;
            case 2:
                line = _t(MSG_EDITOR, 123);
                break;
        }
        _addDescription(ss.str(), line); // level description
        _addImage(ss.str(), new Image("art/skilldex/" + imagesLevel[i] + ".frm")); // stat image
        tmp.str() = "";
        tmp << _t(MSG_EDITOR, 113 + i) << " ";
        switch (i)
        {
            case 0:
                tmp << player->level();
                break;
            case 1:
                tmp << player->experience();
                break;
            case 2:
                tmp << expNext;
                break;
        }
        _addLabel(ss.str(), new TextArea(tmp.str(), backgroundX + 32, backgroundY + 280 + 11*i));            // stat value label
    }

    // SKILLS
    std::string imagesSkills[]  = { "gunsml", "gunbig", "energywp", "unarmed", "melee", "throwing", "firstaid", "doctor", "sneak",
                                    "lockpick", "steal", "traps", "science", "repair", "speech", "barter", "gambling", "outdoors"};
    for (unsigned int i = 0; i != 18; ++i)
    {
        std::stringstream ss;
        ss << "skills_" << (i+1);
        _addTitle(ss.str(), _t(MSG_SKILLS, 100 + i));
        _addDescription(ss.str(), _t(MSG_SKILLS, 200 + i));
        _addImage(ss.str(),  new Image("art/skilldex/" + imagesSkills[i] + ".frm"));
        _addLabel(ss.str(),  new TextArea(_t(MSG_SKILLS, 100 + i), backgroundX+377, backgroundY+27+11*i))->setWidth(240);
        _addLabel(ss.str() + "_value",  new TextArea("", backgroundX+577, backgroundY+27+11*i));
    }
    // Free skill points counts
    _addCounter("skillsPoints", new BigCounter(backgroundX+522, backgroundY+228));

    // HEALTH CONDITION
    std::string imagesHealth[] = { "hitpoint", "poisoned", "radiated", "eyedamag", "armright", "armleft", "legright", "legleft"};
    _addTitle("health_1", _t(MSG_EDITOR, 300));
    _addLabel("health_1", new TextArea(_t(MSG_EDITOR, 300), backgroundX+194, backgroundY+46)); //health
    _addDescription("health_1", _t(MSG_STATS, 207));
    _addImage("health_1", new Image("art/skilldex/" + imagesHealth[0] + ".frm"));

    auto font1_0x183018ff = ResourceManager::getInstance()->font("font1.aaf", 0x183018ff);

    for (unsigned int i = 0; i != 7; ++i)
    {
        std::stringstream ss;
        ss << "health_" << (i+2);
        _addTitle(ss.str(), _t(MSG_EDITOR, 312 + i));
        _addDescription(ss.str(), _t(MSG_EDITOR, 400 + i));
        _addLabel(ss.str(), new TextArea(_t(MSG_EDITOR, 312+i), backgroundX+194, backgroundY+46+13*(i+1)))->setFont(font1_0x183018ff);
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
        _addLabel(ss.str() + "_value",  new TextArea("", backgroundX + 288, backgroundY + 179 + 13*i));
    }

    _addButton("print", new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+345, backgroundY+454));
    _addButton("done",    new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+455, backgroundY+454));
    _addButton("cancel",  new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+554, backgroundY+454));

    auto font3_b89c28ff = ResourceManager::getInstance()->font("font3.aaf", 0xb89c28ff);

    _addLabel("print", new TextArea(_t(MSG_EDITOR, 103), backgroundX+365, backgroundY+453))->setFont(font3_b89c28ff);
    _addLabel("next",    new TextArea(_t(MSG_EDITOR, 100), backgroundX+473, backgroundY+453))->setFont(font3_b89c28ff);
    _addLabel("cancel",  new TextArea(_t(MSG_EDITOR, 102), backgroundX+571, backgroundY+453))->setFont(font3_b89c28ff);
    _addLabel("name",    new TextArea(Game::getInstance()->player()->name(), backgroundX+17, backgroundY+7))->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER)->setFont(font3_b89c28ff);
    _addLabel("age",     new TextArea(_t(MSG_EDITOR, 104), backgroundX+163, backgroundY+7))->setFont(font3_b89c28ff);
    _addLabel("gender",  new TextArea(_t(MSG_EDITOR, Game::getInstance()->player()->gender() == GENDER::MALE ? 107 : 108), backgroundX+250, backgroundY+7))->setFont(font3_b89c28ff);

    _addLabel("label_1", new TextArea(_t(MSG_EDITOR, 112), backgroundX+398, backgroundY+233))->setFont(font3_b89c28ff); // skill points on tag skills place!
    _addLabel("label_3", new TextArea(_t(MSG_EDITOR, 117), backgroundX+383, backgroundY+5))->setFont(font3_b89c28ff);  // skills

    _addTitle("label_1", _t(MSG_EDITOR, 112));
    _addTitle("label_2", _t(MSG_EDITOR, 146));
    _addTitle("label_3", _t(MSG_EDITOR, 150));
    _addTitle("label_4", _t(MSG_EDITOR, 144));
    _addDescription("label_1", _t(MSG_EDITOR, 131));
    _addDescription("label_2", _t(MSG_EDITOR, 147));
    _addDescription("label_3", _t(MSG_EDITOR, 151));
    _addDescription("label_4", _t(MSG_EDITOR, 145));
    _addImage("label_1", new Image("art/skilldex/skills.frm"));
    _addImage("label_2", new Image("art/skilldex/traits.frm"));
    _addImage("label_3", new Image("art/skilldex/skills.frm"));
    _addImage("label_4", new Image("art/skilldex/skills.frm"));

    // Name label -- ex Name change button
    //_addButton("name",  std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PLAYER_NAME, backgroundX+13, backgroundY+0)));
    auto nameLabel = new Image("art/intrface/nameoff.frm");
    nameLabel->setX(backgroundX+13);
    nameLabel->setY(backgroundY+0);
    addUI(nameLabel);

    // Age label -- ex Age change button
    //_addButton("age",  std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PLAYER_AGE, backgroundX+156, backgroundY+0)));
    auto ageLabel = new Image("art/intrface/ageoff.frm");
    ageLabel->setX(backgroundX+156);
    ageLabel->setY(backgroundY+0);
    addUI(ageLabel);

    // Gender label -- ex Gender change button
    //_addButton("gender",  std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PLAYER_GENDER, backgroundX+236, backgroundY+0)));
    auto genderLabel = new Image("art/intrface/sexoff.frm");
    genderLabel->setX(backgroundX+236);
    genderLabel->setY(backgroundY+0);
    addUI(genderLabel);

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
    _description->setFont(font1_000000ff)->setWidth(140)->setHeight(120)->setWordWrap(true);
    addUI(_description);
}

TextArea* PlayerEdit::_addLabel(const std::string& name, TextArea* label)
{
    _labels.insert(std::pair<std::string,TextArea*>(name, label));
    return label;
}

ImageButton* PlayerEdit::_addButton(const std::string& name, ImageButton* button)
{
    _buttons.insert(std::pair<std::string,ImageButton*>(name, button));
    return button;
}

BigCounter* PlayerEdit::_addCounter(const std::string& name, BigCounter* counter)
{
    _counters.insert(std::pair<std::string,BigCounter*>(name, counter));
    return counter;
}

HiddenMask* PlayerEdit::_addMask(const std::string& name, HiddenMask* mask)
{
    _masks.insert(std::pair<std::string,HiddenMask*>(name, mask));
    return mask;
}

void PlayerEdit::_addTitle(const std::string& name, std::string title)
{
    _titles.insert(std::pair<std::string,std::string>(name, title));
}

void PlayerEdit::_addDescription(const std::string& name, std::string description)
{
    _descriptions.insert(std::pair<std::string,std::string>(name, description));
}

void PlayerEdit::_addImage(const std::string& name, Image* image)
{
    _images.insert(std::pair<std::string, Image*>(name, image));
}

void PlayerEdit::think()
{
    State::think();
    auto player = Game::getInstance()->player();

    *_labels.at("name") = player->name();
    *_labels.at("age") = _t(MSG_EDITOR, 104) + " " + std::to_string(player->age());
    *_labels.at("gender") = _t(MSG_EDITOR, player->gender() == GENDER::MALE ? 107 : 108);

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
    *_labels.at("params_10_value")+= "%";

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
        _labels.at(ss.str())->setText(_t(MSG_STATS, 300 + (val < 1 ? 1 : val)));
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

//        if (name.find("traits_") == 0)
//        {
//            unsigned int number = atoi(name.substr(7).c_str());
//            it->second->setFont(player->trait(number - 1) ? font1_a0a0a0ff : font1_3ff800ff);
//        }

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

//        if (name.find("traits_") == 0)
//        {
//            unsigned int number = atoi(name.substr(7).c_str());
//            it->second->setFont(player->trait(number - 1) ? font1_ffffffff : font1_ffff7fff);
//        }

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

void PlayerEdit::onButtonClick(MouseEvent* event)
{
    auto sender = dynamic_cast<ImageButton*>(event->emitter());

    for(auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        if (it->second == sender)
        {
            std::string name = it->first;

            if (name == "cancel") return doCancel();
            if (name == "done") return doDone();

        }
    }
}

void PlayerEdit::onLabelClick(MouseEvent* event)
{
    for(auto it = _labels.begin(); it != _labels.end(); ++it)
    {
        std::string name = it->first;
//        if (it->second.get() == event->emitter())
        if (it->second == event->emitter())
        {
//            if (name.find("stats_") == 0 || name.find("traits_") == 0 || name.find("skills_") == 0 || name.find("health_") == 0 || name.find("params_") == 0 || name.find("label_") == 0 || name.find("level_") == 0 )
            if (name.find("stats_") == 0 || name.find("skills_") == 0 || name.find("health_") == 0 || name.find("params_") == 0 || name.find("label_") == 0 || name.find("level_") == 0 )
//            if (name.find("stats_") == 0 || name.find("skills_") == 0 || name.find("health_") == 0 || name.find("params_") == 0 || name.find("label_") == 0 )
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

void PlayerEdit::onMaskClick(MouseEvent* event)
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

void PlayerEdit::doCancel()
{
    Game::getInstance()->popState();
}

void PlayerEdit::doDone()
{
    Game::getInstance()->popState();
}

void PlayerEdit::doPrint()
{
    // @TODO: implement
}

void PlayerEdit::onStateActivate(StateEvent* event)
{
    Game::getInstance()->mouse()->pushState(Mouse::BIG_ARROW);
}

void PlayerEdit::onStateDeactivate(StateEvent* event)
{
    Game::getInstance()->mouse()->popState();
}

void PlayerEdit::onKeyDown(KeyboardEvent* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_c:
            doCancel();
            break;
        case SDLK_RETURN:
        case SDLK_d:
            doDone();
            break;
        case SDLK_p:
            doPrint();
            break;
    }
}


}
}
