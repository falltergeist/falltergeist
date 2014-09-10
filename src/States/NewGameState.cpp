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
#include "../States/NewGameState.h"
#include "../States/PlayerEditState.h"
#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../UI/ImageList.h"
#include "../Game/GameDudeObject.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/Image.h"

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
    add(new Image("art/intrface/pickchar.frm"));

    // Begin game button
    auto beginGameButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 322);
    beginGameButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onBeginGameButtonClick);

    // Edit character button
    auto editButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 436, 319);
    editButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onEditButtonClick);
    
    // Create character button
    auto createButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 424);
    createButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onCreateButtonClick);

    // Back to mainmenu button
    auto backButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 461, 424);
    backButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onBackButtonClick);

    // Previous character button
    auto prevCharacterButton = new ImageButton(ImageButton::TYPE_LEFT_ARROW, 292, 320);
    prevCharacterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onPrevCharacterButtonClick);

    // Next character button
    auto nextCharacterButton = new ImageButton(ImageButton::TYPE_RIGHT_ARROW, 318, 320);
    nextCharacterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &NewGameState::onNextCharacterButtonClick);

    // Characters images
    _selectedCharacter = 0;
    _characterImages = new ImageList({
                                          "art/intrface/combat.frm",
                                          "art/intrface/stealth.frm",
                                          "art/intrface/diplomat.frm"
                                      }, 27, 23);

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
    _playerName = new TextArea(350, 50);

    _playerStats1 = new TextArea(0, 80);
    _playerStats1->setWidth(370)
                 ->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _playerStats2 = new TextArea(374, 80);
    _playerBio = new TextArea(430, 50);


    add(beginGameButton);
    add(editButton);
    add(createButton);
    add(backButton);
    add(prevCharacterButton);
    add(nextCharacterButton);

    add(_characterImages);
    add(_playerName);
    add(_playerStats1);
    add(_playerStats2);
    add(_playerBio);
    
    changeCharacter();
}

void NewGameState::think()
{
    State::think();
}

void NewGameState::onBackButtonClick(MouseEvent* event)
{
    _game->popState();
}

void NewGameState::onPrevCharacterButtonClick(MouseEvent* event)
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

void NewGameState::onNextCharacterButtonClick(MouseEvent* event)
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
    
    _playerBio->setText(dude->biography());
    _playerName->setText(dude->name());

    _characterImages->setCurrentImage(_selectedCharacter);
}

std::string NewGameState::statToString(unsigned int stat)
{
    auto msg = ResourceManager::msgFileType("text/english/game/stat.msg");
    return msg->message(stat+300)->text();
}

void NewGameState::onEditButtonClick(MouseEvent* event)
{
    _game->setPlayer(_characters.at(_selectedCharacter));
    _game->pushState(std::shared_ptr<PlayerEditState>(new PlayerEditState()));
}

void NewGameState::onCreateButtonClick(MouseEvent* event)
{
    auto none = std::shared_ptr<GameDudeObject>(new GameDudeObject());
    none->loadFromGCDFile(ResourceManager::gcdFileType("premade/blank.gcd"));
    _selectedCharacter = _characters.size() + 1; // to guarantee deletion of all created dudes in destructor
    _game->setPlayer(none);
    _game->pushState(std::shared_ptr<PlayerEditState>(new PlayerEditState()));
}

void NewGameState::onBeginGameButtonClick(MouseEvent* event)
{
    _game->setPlayer(_characters.at(_selectedCharacter));
    _game->setState(std::shared_ptr<LocationState>(new LocationState()));
}

}
