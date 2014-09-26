/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameDudeObject.h"
#include "../States/NewGameState.h"
#include "../States/LocationState.h"
#include "../States/PlayerCreateState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

NewGameState::NewGameState() : State()
{
}

NewGameState::~NewGameState()
{
    while(!_characters.empty())
    {
        if (_characters.back() != Game::getInstance()->player()) delete _characters.back();
        _characters.pop_back();
    }
}

void NewGameState::init()
{
    if (_initialized) return;
    State::init();

    auto renderer = Game::getInstance()->renderer();

    setX((renderer->width()  - 640)*0.5);
    setY((renderer->height() - 480)*0.5);

    addUI("background", new Image("art/intrface/pickchar.frm"));

    auto beginGameButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 322));
    beginGameButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onBeginGameButtonClick);

    auto editButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 436, 319));
    editButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onEditButtonClick);

    auto createButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 424));
    createButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onCreateButtonClick);

    auto backButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 461, 424));
    backButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onBackButtonClick);

    auto prevCharacterButton = addUI(new ImageButton(ImageButton::TYPE_LEFT_ARROW, 292, 320));
    prevCharacterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onPrevCharacterButtonClick);

    auto nextCharacterButton = addUI(new ImageButton(ImageButton::TYPE_RIGHT_ARROW, 318, 320));
    nextCharacterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onNextCharacterButtonClick);

    addUI("images", new ImageList({
                                      "art/intrface/combat.frm",
                                      "art/intrface/stealth.frm",
                                      "art/intrface/diplomat.frm"
                                  }, 27, 23));

    addUI("name", new TextArea(300, 40));

    addUI("stats_1", new TextArea(0, 70));
    getTextArea("stats_1")->setWidth(362)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    addUI("stats_2", new TextArea(374, 70));
    addUI("bio",     new TextArea(437, 40));

    addUI("stats_3", new TextArea(294, 150));
    getTextArea("stats_3")->setWidth(85)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    addUI("hit_points_max", new TextArea(383, 150));
    addUI("armor_class",    new TextArea(383, 150 + 10));
    addUI("action_points",  new TextArea(383, 150 + 10*2));
    addUI("melee_damage",   new TextArea(383, 150 + 10*3));

    addUI("skills", new TextArea(289, 200));
    getTextArea("skills")->setWidth(90)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    addUI("skills_values", new TextArea(383, 200));

    auto combat = new GameDudeObject();
    combat->loadFromGCDFile(ResourceManager::gcdFileType("premade/combat.gcd"));
    combat->setBiography(ResourceManager::bioFileType("premade/combat.bio")->text());
    _characters.push_back(combat);

    auto stealth = new GameDudeObject();
    stealth->loadFromGCDFile(ResourceManager::gcdFileType("premade/stealth.gcd"));
    stealth->setBiography(ResourceManager::bioFileType("premade/stealth.bio")->text());
    _characters.push_back(stealth);

    auto diplomat = new GameDudeObject();
    diplomat->loadFromGCDFile(ResourceManager::gcdFileType("premade/diplomat.gcd"));
    diplomat->setBiography(ResourceManager::bioFileType("premade/diplomat.bio")->text());
    _characters.push_back(diplomat);

    _changeCharacter();
}

void NewGameState::think()
{
    State::think();
}

void NewGameState::onBackButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

void NewGameState::onPrevCharacterButtonClick(std::shared_ptr<MouseEvent> event)
{
    if (_selectedCharacter > 0)
    {
        _selectedCharacter--;
    }
    else
    {
        _selectedCharacter = 2;
    }
    _changeCharacter();
}

void NewGameState::onNextCharacterButtonClick(std::shared_ptr<MouseEvent> event)
{
    if (_selectedCharacter < 2)
    {
        _selectedCharacter++;
    }
    else
    {
        _selectedCharacter = 0;
    }
    _changeCharacter();
}

void NewGameState::_changeCharacter()
{
    auto dude = _characters.at(_selectedCharacter);
    std::stringstream ss;
    auto msg = ResourceManager::msgFileType("text/english/game/stat.msg");
    ss << msg->message(100)->text() << " " << (dude->stat(0) < 10 ? "0" : "") << dude->stat(0) << "\n"
       << msg->message(101)->text() << " " << (dude->stat(1) < 10 ? "0" : "") << dude->stat(1) << "\n"
       << msg->message(102)->text() << " " << (dude->stat(2) < 10 ? "0" : "") << dude->stat(2) << "\n"
       << msg->message(103)->text() << " " << (dude->stat(3) < 10 ? "0" : "") << dude->stat(3) << "\n"
       << msg->message(104)->text() << " " << (dude->stat(4) < 10 ? "0" : "") << dude->stat(4) << "\n"
       << msg->message(105)->text() << " " << (dude->stat(5) < 10 ? "0" : "") << dude->stat(5) << "\n"
       << msg->message(106)->text() << " " << (dude->stat(6) < 10 ? "0" : "") << dude->stat(6) << "\n";
    getTextArea("stats_1")->setText(ss.str());

    ss.str("");
    ss << _statToString(dude->stat(0)) << "\n"
       << _statToString(dude->stat(1)) << "\n"
       << _statToString(dude->stat(2)) << "\n"
       << _statToString(dude->stat(3)) << "\n"
       << _statToString(dude->stat(4)) << "\n"
       << _statToString(dude->stat(5)) << "\n"
       << _statToString(dude->stat(6)) << "\n";
    getTextArea("stats_2")->setText(ss.str());

    auto msgMisc = ResourceManager::msgFileType("text/english/game/misc.msg");
    ss.str("");
    ss << msgMisc->message(16)->text() << "\n" // Hit Points
       << msg->message(109)->text() << "\n"    // Armor Class
       << msgMisc->message(15)->text() << "\n" // Action Points
       << msg->message(111)->text();           // Melee Damage
    getTextArea("stats_3")->setText(ss.str());

    getTextArea("bio")->setText(dude->biography());
    getTextArea("name")->setText(dude->name());

    getImageList("images")->setCurrentImage(_selectedCharacter);

    // Hit Points
    ss.str("");
    ss << dude->hitPointsMax() << "/" << dude->hitPointsMax();
    getTextArea("hit_points_max")->setText(ss.str());

    getTextArea("armor_class")->setText(dude->armorClass());
    getTextArea("action_points")->setText(dude->actionPoints());
    getTextArea("melee_damage")->setText(dude->meleeDamage());

    // Tagged skills
    std::string txt = "";
    std::string values = "";
    for (unsigned int i=0; i<17; i++)
    {
        if (dude->skill(i))
        {
            if (txt != "")
            {
                txt += "\n";
                values += "%\n";
            }
            txt += ResourceManager::msgFileType("text/english/game/skill.msg")->message(100 + i)->text();
            values += std::to_string(dude->skillValue(i));
        }
    }
    values += "%"; // final % char to string

    // traits
    for (unsigned int i=0; i != 16; ++i)
    {
        if (dude->trait(i))
        {
            txt += "\n" + ResourceManager::msgFileType("text/english/game/trait.msg")->message(100 + i)->text();
        }
    }
    getTextArea("skills")->setText(txt);
    getTextArea("skills_values")->setText(values);
}

std::string NewGameState::_statToString(unsigned int stat)
{
    auto msg = ResourceManager::msgFileType("text/english/game/stat.msg");
    return msg->message(stat+300)->text();
}

void NewGameState::onEditButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->setPlayer(_characters.at(_selectedCharacter));
    Game::getInstance()->pushState(new PlayerCreateState());
}

void NewGameState::onCreateButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto none = new GameDudeObject();
    none->loadFromGCDFile(ResourceManager::gcdFileType("premade/blank.gcd"));
    Game::getInstance()->setPlayer(none);
    Game::getInstance()->pushState(new PlayerCreateState());
}

void NewGameState::onBeginGameButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto player = _characters.at(_selectedCharacter);
    player->setHitPoints(player->hitPointsMax());
    Game::getInstance()->setPlayer(player);
    Game::getInstance()->setState(new LocationState());
}

}
