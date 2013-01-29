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

#include "../States/NewGameState.h"
#include "../States/PlayerEditState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SurfaceSet.h"
#include "../Engine/Player.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include <iostream>
#include <sstream>

namespace Falltergeist
{

NewGameState::NewGameState(Game * game) : State(game)
{
}

NewGameState::~NewGameState()
{
}

void NewGameState::init()
{
    State::init();
    _isFullscreen = true;
    // background
    add(ResourceManager::surface("art/intrface/pickchar.frm"));

    // Begin game button
    ImageButton * beginGameButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 81, 322);

    // Edit character button
    ImageButton * editButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 436, 319);
    editButton->onLeftButtonClick((EventHandler) &NewGameState::onEditButtonClick);
    
    // Create character button
    ImageButton * createButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 81, 424);
    createButton->onLeftButtonClick((EventHandler) &NewGameState::onCreateButtonClick);

    // Back to mainmenu button
    ImageButton * backButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 461, 424);
    backButton->onLeftButtonClick((EventHandler) &NewGameState::onBackButtonClick);

    // Previous character button
    ImageButton * prevCharacterButton = new ImageButton("art/intrface/slu.frm", "art/intrface/sld.frm", 292, 320);
    prevCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onPrevCharacterButtonClick);

    // Next character button
    ImageButton * nextCharacterButton = new ImageButton("art/intrface/sru.frm", "art/intrface/srd.frm", 318, 320);
    nextCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onNextCharacterButtonClick);

    // Characters images
    _selectedCharacter = 0;
    _characterImages = new SurfaceSet(27,23);
    _characterImages->addSurface(ResourceManager::surface("art/intrface/combat.frm"));
    _characterImages->addSurface(ResourceManager::surface("art/intrface/stealth.frm"));
    _characterImages->addSurface(ResourceManager::surface("art/intrface/diplomat.frm"));



    _characters = new std::vector<Player *>;
    _characters->push_back(new Player(ResourceManager::gcdFileType("premade/combat.gcd")));
    _characters->at(0)->setBio(ResourceManager::bioFileType("premade/combat.bio")->text());
    _characters->push_back(new Player(ResourceManager::gcdFileType("premade/stealth.gcd")));
    _characters->at(1)->setBio(ResourceManager::bioFileType("premade/stealth.bio")->text());
    _characters->push_back(new Player(ResourceManager::gcdFileType("premade/diplomat.gcd")));
    _characters->at(2)->setBio(ResourceManager::bioFileType("premade/diplomat.bio")->text());
    
    // Character data textareas
    _playerName = new TextArea("",350,50);
    _playerName->setFont("font1.aaf");

    _playerStats1 = new TextArea("",0,80);
    _playerStats1->setWidth(370);
    _playerStats1->setFont("font1.aaf");
    _playerStats1->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    _playerStats2 = new TextArea("",374,80);
    _playerStats2->setFont("font1.aaf");

    _playerBio = new TextArea("",430,50);
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

void NewGameState::onBackButtonClick()
{
    _game->popState();
}

void NewGameState::onPrevCharacterButtonClick()
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

void NewGameState::onNextCharacterButtonClick()
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
    ss   << _t(100,"text/english/game/stat.msg") << " " << (player->strength < 10 ? "0" : "")     << player->strength     << "\r\n"
         << _t(101,"text/english/game/stat.msg") << " " << (player->perception < 10 ? "0" : "")   << player->perception   << "\r\n"
         << _t(102,"text/english/game/stat.msg") << " " << (player->endurance < 10 ? "0" : "")    << player->endurance    << "\r\n"
         << _t(103,"text/english/game/stat.msg") << " " << (player->charisma < 10 ? "0" : "")     << player->charisma     << "\r\n"
         << _t(104,"text/english/game/stat.msg") << " " << (player->intelligence < 10 ? "0" : "") << player->intelligence << "\r\n"
         << _t(105,"text/english/game/stat.msg") << " " << (player->agility < 10 ? "0" : "")      << player->agility      << "\r\n"
         << _t(106,"text/english/game/stat.msg") << " " << (player->luck < 10 ? "0" : "")         << player->luck         << "\r\n" ;
    _playerStats1->setText(ss.str().c_str());
     
    ss.str("");
    ss << statToString(player->strength) << "\r\n"
       << statToString(player->perception) << "\r\n"
       << statToString(player->endurance) << "\r\n"
       << statToString(player->charisma) << "\r\n"
       << statToString(player->intelligence) << "\r\n"
       << statToString(player->agility) << "\r\n"
       << statToString(player->luck) << "\r\n";
    _playerStats2->setText(ss.str().c_str());
    
    _playerBio->setText(player->bio());
    _playerName->setText(player->name());

    _characterImages->currentSurface = _selectedCharacter;    
}

const char * NewGameState::statToString(unsigned int stat)
{
    return _t(stat+300,"text/english/game/stat.msg");
}

void NewGameState::onEditButtonClick()
{
    _game->setPlayer(_characters->at(_selectedCharacter));
    _game->pushState(new PlayerEditState(_game));
}

void NewGameState::onCreateButtonClick()
{
    _game->setPlayer(new Player(ResourceManager::gcdFileType("premade/blank.gcd")));
    _game->pushState(new PlayerEditState(_game));
}

}
