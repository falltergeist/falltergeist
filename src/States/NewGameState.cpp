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
#include <iostream>
#include <sstream>

// Falltergeist includes
#include "../States/NewGameState.h"
#include "../States/PlayerEditState.h"
#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SurfaceSet.h"
#include "../Engine/Player.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

NewGameState::NewGameState(Game * game) : State(game)
{
    _characters = new std::vector<Player *>;
}


NewGameState::~NewGameState()
{
    while (!_characters->empty())
    {
        delete _characters->back();
        _characters->pop_back();
    }
    delete _characters;
}

void NewGameState::init()
{
    State::init();
    _isFullscreen = true;
    // background
    add(new Surface(ResourceManager::surface("art/intrface/pickchar.frm")));

    // Begin game button
    ImageButton * beginGameButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 322);
    beginGameButton->onLeftButtonClick((EventHandler) &NewGameState::onBeginGameButtonClick);

    // Edit character button
    ImageButton * editButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 436, 319);
    editButton->onLeftButtonClick((EventHandler) &NewGameState::onEditButtonClick);
    
    // Create character button
    ImageButton * createButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 424);
    createButton->onLeftButtonClick((EventHandler) &NewGameState::onCreateButtonClick);

    // Back to mainmenu button
    ImageButton * backButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 461, 424);
    backButton->onLeftButtonClick((EventHandler) &NewGameState::onBackButtonClick);

    // Previous character button
    ImageButton * prevCharacterButton = new ImageButton(ImageButton::TYPE_LEFT_ARROW, 292, 320);
    prevCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onPrevCharacterButtonClick);

    // Next character button
    ImageButton * nextCharacterButton = new ImageButton(ImageButton::TYPE_RIGHT_ARROW, 318, 320);
    nextCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onNextCharacterButtonClick);

    // Characters images
    _selectedCharacter = 0;
    _characterImages = new SurfaceSet({
                                          "art/intrface/combat.frm",
                                          "art/intrface/stealth.frm",
                                          "art/intrface/diplomat.frm"
                                      }, 27, 23);

    _characters->push_back(new Player(ResourceManager::gcdFileType("premade/combat.gcd")));
    _characters->back()->setBio(ResourceManager::bioFileType("premade/combat.bio")->text());
    _characters->push_back(new Player(ResourceManager::gcdFileType("premade/stealth.gcd")));
    _characters->back()->setBio(ResourceManager::bioFileType("premade/stealth.bio")->text());
    _characters->push_back(new Player(ResourceManager::gcdFileType("premade/diplomat.gcd")));
    _characters->back()->setBio(ResourceManager::bioFileType("premade/diplomat.bio")->text());
    
    // Character data textareas
    _playerName = new TextArea(350, 50);
    _playerName->setFont("font1.aaf");

    _playerStats1 = new TextArea(0, 80);
    _playerStats1->setWidth(370);
    _playerStats1->setFont("font1.aaf");
    _playerStats1->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _playerStats2 = new TextArea(374, 80);
    _playerStats2->setFont("font1.aaf");

    _playerBio = new TextArea(430, 50);
    _playerBio->setFont("font1.aaf");


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
}

void NewGameState::onBackButtonClick(Event * event)
{
    _game->popState();
}

void NewGameState::onPrevCharacterButtonClick(Event * event)
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

void NewGameState::onNextCharacterButtonClick(Event * event)
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
    Player * player = _characters->at(_selectedCharacter);
    std::stringstream ss;
    ss   << _t(100,"text/english/game/stat.msg") << " " << (player->strength()    < 10 ? "0" : "") << player->strength()     << "\n"
         << _t(101,"text/english/game/stat.msg") << " " << (player->perception()  < 10 ? "0" : "") << player->perception()   << "\n"
         << _t(102,"text/english/game/stat.msg") << " " << (player->endurance()   < 10 ? "0" : "") << player->endurance()    << "\n"
         << _t(103,"text/english/game/stat.msg") << " " << (player->charisma()    < 10 ? "0" : "") << player->charisma()     << "\n"
         << _t(104,"text/english/game/stat.msg") << " " << (player->intelligence()< 10 ? "0" : "") << player->intelligence() << "\n"
         << _t(105,"text/english/game/stat.msg") << " " << (player->agility()     < 10 ? "0" : "") << player->agility()      << "\n"
         << _t(106,"text/english/game/stat.msg") << " " << (player->luck()        < 10 ? "0" : "") << player->luck()         << "\n" ;
    _playerStats1->setText(ss.str());
     
    ss.str("");
    ss << statToString(player->strength()) << "\n"
       << statToString(player->perception()) << "\n"
       << statToString(player->endurance()) << "\n"
       << statToString(player->charisma()) << "\n"
       << statToString(player->intelligence()) << "\n"
       << statToString(player->agility()) << "\n"
       << statToString(player->luck()) << "\n";
    _playerStats2->setText(ss.str());
    
    _playerBio->setText(player->bio());
    _playerName->setText(player->name());

    _characterImages->currentSurface = _selectedCharacter;    
}

std::string NewGameState::statToString(unsigned int stat)
{
    return _t(stat+300,"text/english/game/stat.msg");
}

void NewGameState::onEditButtonClick(Event * event)
{
    _game->setPlayer(_characters->at(_selectedCharacter));
    _game->pushState(new PlayerEditState(_game));
}

void NewGameState::onCreateButtonClick(Event * event)
{
    _game->setPlayer(new Player(ResourceManager::gcdFileType("premade/blank.gcd")));
    _game->pushState(new PlayerEditState(_game));
}

void NewGameState::onBeginGameButtonClick(Event * event)
{
    _game->setPlayer(_characters->at(_selectedCharacter));
    _game->setState(new LocationState(_game));
}

}
