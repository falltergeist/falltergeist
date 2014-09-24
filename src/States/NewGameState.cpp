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
}

void NewGameState::init()
{
    if (_initialized) return;
    State::init();

    // Background
    auto background = std::shared_ptr<Image>(new Image("art/intrface/pickchar.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Begin game button
    auto beginGameButton= std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+81, backgroundY+322));
    beginGameButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onBeginGameButtonClick);

    // Edit character button
    auto editButton= std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+436, backgroundY+319));
    editButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onEditButtonClick);

    // Create character button
    auto createButton= std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+81, backgroundY+424));
    createButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onCreateButtonClick);

    // Back to mainmenu button
    auto backButton= std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+461, backgroundY+424));
    backButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onBackButtonClick);

    // Previous character button
    auto prevCharacterButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_LEFT_ARROW, backgroundX+292, backgroundY+320));
    prevCharacterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onPrevCharacterButtonClick);

    // Next character button
    auto nextCharacterButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_RIGHT_ARROW, backgroundX+318, backgroundY+320));
    nextCharacterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onNextCharacterButtonClick);

    // Characters images
    _selectedCharacter = 0;
    _characterImages = std::shared_ptr<ImageList>(new ImageList({
                                          "art/intrface/combat.frm",
                                          "art/intrface/stealth.frm",
                                          "art/intrface/diplomat.frm"
                                      }, backgroundX+27, backgroundY+23));

    auto combat = std::shared_ptr<GameDudeObject>(new GameDudeObject());
    combat->loadFromGCDFile(ResourceManager::gcdFileType("premade/combat.gcd"));
    combat->setBiography(ResourceManager::bioFileType("premade/combat.bio")->text());
    _characters.push_back(combat);

    auto stealth = std::shared_ptr<GameDudeObject>(new GameDudeObject());
    stealth->loadFromGCDFile(ResourceManager::gcdFileType("premade/stealth.gcd"));
    stealth->setBiography(ResourceManager::bioFileType("premade/stealth.bio")->text());
    _characters.push_back(stealth);

    auto diplomat = std::shared_ptr<GameDudeObject>(new GameDudeObject());
    diplomat->loadFromGCDFile(ResourceManager::gcdFileType("premade/diplomat.gcd"));
    diplomat->setBiography(ResourceManager::bioFileType("premade/diplomat.bio")->text());
    _characters.push_back(diplomat);

    // Character data textareas
    _playerName = std::shared_ptr<TextArea>(new TextArea(backgroundX+300, backgroundY+40));

    _playerStats1 = std::shared_ptr<TextArea>(new TextArea(backgroundX+0, backgroundY+70));
    _playerStats1->setWidth(362)
                 ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _playerStats2 = std::shared_ptr<TextArea>(new TextArea(backgroundX+374, backgroundY+70));
    _playerBio = std::shared_ptr<TextArea>(new TextArea(backgroundX+437, backgroundY+40));

    _playerStats3 = std::shared_ptr<TextArea>(new TextArea(backgroundX+294, backgroundY+150));
    _playerStats3->setWidth(85)
                 ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _playerHitPointsMax = std::shared_ptr<TextArea>(new TextArea(backgroundX+383, backgroundY+150));
    _playerArmorClass = std::shared_ptr<TextArea>(new TextArea(backgroundX+383, backgroundY+150+10));
    _playerActionPoints = std::shared_ptr<TextArea>(new TextArea(backgroundX+383, backgroundY+150+10*2));
    _playerMeleeDamage = std::shared_ptr<TextArea>(new TextArea(backgroundX+383, backgroundY+150+10*3));

    _playerSkills = std::shared_ptr<TextArea>(new TextArea(backgroundX+289, backgroundY+200));
    _playerSkills->setWidth(90)
                 ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _playerSkillsValues = std::shared_ptr<TextArea>(new TextArea(backgroundX+383, backgroundY+200));

    _playerTraits = std::shared_ptr<TextArea>(new TextArea(backgroundX+294, backgroundY+230));
    _playerTraits->setWidth(85)
                 ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    addUI(background);
    addUI(beginGameButton);
    addUI(editButton);
    addUI(createButton);
    addUI(backButton);
    addUI(prevCharacterButton);
    addUI(nextCharacterButton);

    addUI(_characterImages);
    addUI(_playerName);
    addUI(_playerStats1);
    addUI(_playerStats2);
    addUI(_playerStats3);
    addUI(_playerBio);
    addUI(_playerHitPointsMax);
    addUI(_playerArmorClass);
    addUI(_playerActionPoints);
    addUI(_playerMeleeDamage);
    addUI(_playerSkills);
    addUI(_playerSkillsValues);
    addUI(_playerTraits);

    changeCharacter();
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
    changeCharacter();
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
    changeCharacter();
}

void NewGameState::changeCharacter()
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
    _playerStats1->setText(ss.str());

    ss.str("");
    ss << statToString(dude->stat(0)) << "\n"
       << statToString(dude->stat(1)) << "\n"
       << statToString(dude->stat(2)) << "\n"
       << statToString(dude->stat(3)) << "\n"
       << statToString(dude->stat(4)) << "\n"
       << statToString(dude->stat(5)) << "\n"
       << statToString(dude->stat(6)) << "\n";
    _playerStats2->setText(ss.str());

    auto msgMisc = ResourceManager::msgFileType("text/english/game/misc.msg");
    ss.str("");
    ss << msgMisc->message(16)->text() << "\n" // Hit Points
       << msg->message(109)->text() << "\n"    // Armor Class
       << msgMisc->message(15)->text() << "\n" // Action Points
       << msg->message(111)->text();           // Melee Damage
    _playerStats3->setText(ss.str());

    _playerBio->setText(dude->biography());
    _playerName->setText(dude->name());

    _characterImages->setCurrentImage(_selectedCharacter);

    // Hit Points
    ss.str("");
    ss << dude->hitPointsMax() << "/" << dude->hitPointsMax();
    _playerHitPointsMax->setText(ss.str());

    _playerArmorClass->setText(dude->armorClass());
    _playerActionPoints->setText(dude->actionPoints());
    _playerMeleeDamage->setText(dude->meleeDamage());

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
    _playerSkills->setText(txt);
    _playerSkillsValues->setText(values);

    // traits
    txt = "";
    for (unsigned int i=0; i<16; i++)
    {
        if (dude->trait(i))
        {
            if (txt != "")
            {
                txt += "\n";
            }
            txt += ResourceManager::msgFileType("text/english/game/trait.msg")->message(100 + i)->text();
        }
    }
    _playerTraits->setText(txt);

}

std::string NewGameState::statToString(unsigned int stat)
{
    auto msg = ResourceManager::msgFileType("text/english/game/stat.msg");
    return msg->message(stat+300)->text();
}

void NewGameState::onEditButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->setPlayer(_characters.at(_selectedCharacter));
    Game::getInstance()->pushState(std::shared_ptr<PlayerCreateState>(new PlayerCreateState()));
}

void NewGameState::onCreateButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto none = std::shared_ptr<GameDudeObject>(new GameDudeObject());
    none->loadFromGCDFile(ResourceManager::gcdFileType("premade/blank.gcd"));
    Game::getInstance()->setPlayer(none);
    Game::getInstance()->pushState(std::shared_ptr<PlayerCreateState>(new PlayerCreateState()));
}

void NewGameState::onBeginGameButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto player = _characters.at(_selectedCharacter);
    player->setHitPoints(player->hitPointsMax());
    Game::getInstance()->setPlayer(player);
    Game::getInstance()->setState(std::shared_ptr<LocationState>(new LocationState()));

}

}
