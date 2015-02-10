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
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Event/StateEvent.h"
#include "../Game/DudeObject.h"
#include "../State/NewGame.h"
#include "../State/Location.h"
#include "../State/PlayerCreate.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

NewGame::NewGame() : State()
{
}

NewGame::~NewGame()
{
    while(!_characters.empty())
    {
        if (_characters.back() != Game::getInstance()->player()) delete _characters.back();
        _characters.pop_back();
    }
}

void NewGame::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(true);
    setModal(true);

    auto renderer = Game::getInstance()->renderer();

    setX((renderer->width()  - 640)*0.5);
    setY((renderer->height() - 480)*0.5);

    auto background = addUI("background", new Image("art/intrface/pickchar.frm"));
    background->addEventHandler("keydown", [this](Event* event){ this->onKeyPress(dynamic_cast<KeyboardEvent*>(event)); });

    auto beginGameButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 322));
    beginGameButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onBeginGameButtonClick(dynamic_cast<MouseEvent*>(event)); });

    auto editButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 436, 319));
    editButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onEditButtonClick(dynamic_cast<MouseEvent*>(event)); });

    auto createButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 81, 424));
    createButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onCreateButtonClick(dynamic_cast<MouseEvent*>(event)); });

    auto backButton = addUI(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 461, 424));
    backButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onBackButtonClick(dynamic_cast<MouseEvent*>(event)); });

    auto prevCharacterButton = addUI(new ImageButton(ImageButton::TYPE_LEFT_ARROW, 292, 320));
    prevCharacterButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onPrevCharacterButtonClick(dynamic_cast<MouseEvent*>(event)); });

    auto nextCharacterButton = addUI(new ImageButton(ImageButton::TYPE_RIGHT_ARROW, 318, 320));
    nextCharacterButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onNextCharacterButtonClick(dynamic_cast<MouseEvent*>(event)); });

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

    addUI("stats3_values", new TextArea(383, 150));

    auto combat = new Game::GameDudeObject();
    combat->loadFromGCDFile(ResourceManager::gcdFileType("premade/combat.gcd"));
    combat->setBiography(ResourceManager::bioFileType("premade/combat.bio")->text());
    _characters.push_back(combat);

    auto stealth = new Game::GameDudeObject();
    stealth->loadFromGCDFile(ResourceManager::gcdFileType("premade/stealth.gcd"));
    stealth->setBiography(ResourceManager::bioFileType("premade/stealth.bio")->text());
    _characters.push_back(stealth);

    auto diplomat = new Game::GameDudeObject();
    diplomat->loadFromGCDFile(ResourceManager::gcdFileType("premade/diplomat.gcd"));
    diplomat->setBiography(ResourceManager::bioFileType("premade/diplomat.bio")->text());
    _characters.push_back(diplomat);

    _changeCharacter();
}

void NewGame::think()
{
    State::think();
}

void NewGame::doBeginGame()
{
    auto player = _characters.at(_selectedCharacter);
    Game::getInstance()->setPlayer(player);
    Game::getInstance()->setState(new Location());
}

void NewGame::doEdit()
{
    Game::getInstance()->setPlayer(_characters.at(_selectedCharacter));
    Game::getInstance()->pushState(new PlayerCreate()); 
}

void NewGame::doCreate()
{
    auto none = new Game::GameDudeObject();
    none->loadFromGCDFile(ResourceManager::gcdFileType("premade/blank.gcd"));
    Game::getInstance()->setPlayer(none);
    Game::getInstance()->pushState(new PlayerCreate());
}

void NewGame::doBack()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event* event){ this->onBackFadeDone(dynamic_cast<StateEvent*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void NewGame::onBackButtonClick(MouseEvent* event)
{
    doBack();
}

void NewGame::onBackFadeDone(StateEvent* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->popState();
}

void NewGame::onPrevCharacterButtonClick(MouseEvent* event)
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

void NewGame::onNextCharacterButtonClick(MouseEvent* event)
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

void NewGame::_changeCharacter()
{
    auto dude = _characters.at(_selectedCharacter);
    std::stringstream ss;
    auto msg = ResourceManager::msgFileType("text/english/game/stat.msg");
    ss  << msg->message(100)->text() << " " << (dude->stat(0) < 10 ? "0" : "") << dude->stat(0) << "\n"
        << msg->message(101)->text() << " " << (dude->stat(1) < 10 ? "0" : "") << dude->stat(1) << "\n"
        << msg->message(102)->text() << " " << (dude->stat(2) < 10 ? "0" : "") << dude->stat(2) << "\n"
        << msg->message(103)->text() << " " << (dude->stat(3) < 10 ? "0" : "") << dude->stat(3) << "\n"
        << msg->message(104)->text() << " " << (dude->stat(4) < 10 ? "0" : "") << dude->stat(4) << "\n"
        << msg->message(105)->text() << " " << (dude->stat(5) < 10 ? "0" : "") << dude->stat(5) << "\n"
        << msg->message(106)->text() << " " << (dude->stat(6) < 10 ? "0" : "") << dude->stat(6) << "\n";
    getTextArea("stats_1")->setText(ss.str());

    ss.str("");
    ss  << _statToString(dude->stat(0)) << "\n"
        << _statToString(dude->stat(1)) << "\n"
        << _statToString(dude->stat(2)) << "\n"
        << _statToString(dude->stat(3)) << "\n"
        << _statToString(dude->stat(4)) << "\n"
        << _statToString(dude->stat(5)) << "\n"
        << _statToString(dude->stat(6)) << "\n";
    getTextArea("stats_2")->setText(ss.str());

    getTextArea("bio")->setText(dude->biography());
    getTextArea("name")->setText(dude->name());
    getImageList("images")->setCurrentImage(_selectedCharacter);

    auto msgMisc = ResourceManager::msgFileType("text/english/game/misc.msg");

    std::string stats3  = msgMisc->message(16)->text() +  "\n"    // Hit Points
                        + msg->message(109)->text()    + "\n"     // Armor Class
                        + msgMisc->message(15)->text() + "\n"     // Action Points
                        + msg->message(111)->text()    + "\n";    // Melee Damage

    std::string stats3_values   = std::to_string(dude->hitPointsMax()) + "/" + std::to_string(dude->hitPointsMax()) + "\n"
                                + std::to_string(dude->armorClass())   + "\n"
                                + std::to_string(dude->actionPoints()) + "\n"
                                + std::to_string(dude->meleeDamage())  + "\n";

    for (unsigned int i=0; i != 17; ++i) if (dude->skillTagged(i))
    {
        stats3 += "\n" + ResourceManager::msgFileType("text/english/game/skill.msg")->message(100 + i)->text();
        stats3_values += "\n" + std::to_string(dude->skillValue(i)) + "%";
    }
    for (unsigned int i=0; i != 16; ++i) if (dude->traitTagged(i))
    {
        stats3 += "\n" + ResourceManager::msgFileType("text/english/game/trait.msg")->message(100 + i)->text();
    }
    getTextArea("stats_3")->setText(stats3);
    getTextArea("stats3_values")->setText(stats3_values);
}

std::string NewGame::_statToString(unsigned int stat)
{
    auto msg = ResourceManager::msgFileType("text/english/game/stat.msg");
    return msg->message(stat+300)->text();
}

void NewGame::onEditButtonClick(MouseEvent* event)
{
    doEdit();
}

void NewGame::onCreateButtonClick(MouseEvent* event)
{
    doCreate();
}

void NewGame::onBeginGameButtonClick(MouseEvent* event)
{
    doBeginGame();
}

void NewGame::onKeyPress(KeyboardEvent* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_b:
            doBack();
            break;
        case SDLK_t:
            doBeginGame();
            break;
        case SDLK_c:
            doCreate();
            break;
        case SDLK_m:
            doEdit();
            break;
    }
}

void NewGame::onStateActivate(StateEvent* event)
{
    Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
}


}
}
