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

// Related headers
#include "../State/MainMenu.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Event/State.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Credits.h"
#include "../State/LoadGame.h"
#include "../State/Movie.h"
#include "../State/NewGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Animation.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

MainMenu::MainMenu() : State()
{
}

MainMenu::~MainMenu()
{
    Game::getInstance()->mixer()->stopMusic();
}

void MainMenu::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::BIG_ARROW);

    auto renderer = Game::getInstance()->renderer();
    setPosition((renderer->size() - Point(640, 480)) / 2);

    addUI("background", new UI::Image("art/intrface/mainmenu.frm"));

    // intro button
    auto introButton = addUI(new UI::ImageButton(UI::ImageButton::Type::MENU_RED_CIRCLE, 30, 19));
    introButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onIntroButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    // new game button
    auto newGameButton = addUI(new UI::ImageButton(UI::ImageButton::Type::MENU_RED_CIRCLE, 30, 19 + 41));
    newGameButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onNewGameButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    // load game button
    auto loadGameButton = addUI(new UI::ImageButton(UI::ImageButton::Type::MENU_RED_CIRCLE, 30, 19 + 41*2));
    loadGameButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onLoadGameButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    // settings button
    auto settingsButton = addUI(new UI::ImageButton(UI::ImageButton::Type::MENU_RED_CIRCLE, 30, 19 + 41*3));
    settingsButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onSettingsButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    // credits button
    auto creditsButton = addUI(new UI::ImageButton(UI::ImageButton::Type::MENU_RED_CIRCLE, 30, 19 + 41*4));
    creditsButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onCreditsButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    // exit button
    auto exitButton = addUI(new UI::ImageButton(UI::ImageButton::Type::MENU_RED_CIRCLE, 30, 19 + 41*5));
    exitButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onExitButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    auto font4 = ResourceManager::getInstance()->font("font4.aaf", 0xb89c28ff);

    // "Intro" label
    auto introButtonLabel = new UI::TextArea(translate("intro", "mainmenu"), 50, 20);
    introButtonLabel->setFont(font4);
    introButtonLabel->setWidth(150);
    introButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    // "New Game" label
    auto newGameButtonLabel = new UI::TextArea(translate("new_game", "mainmenu"), 50, 20 + 41);
    newGameButtonLabel->setFont(font4);
    newGameButtonLabel->setWidth(150);
    newGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    // "Load Game" label
    auto loadGameButtonLabel = new UI::TextArea(translate("load_game", "mainmenu"), 50, 20 + 41*2);
    loadGameButtonLabel->setFont(font4);
    loadGameButtonLabel->setWidth(150);
    loadGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    // "Options" label
    auto optionsButtonLabel = new UI::TextArea(translate("options", "mainmenu"), 50, 20 + 41*3);
    optionsButtonLabel->setFont(font4);
    optionsButtonLabel->setWidth(150);
    optionsButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    // "Credits" label
    auto creditsButtonLabel = new UI::TextArea(translate("credits", "mainmenu"), 50, 20 + 41*4);
    creditsButtonLabel->setFont(font4);
    creditsButtonLabel->setWidth(150);
    creditsButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    // "Exit" label
    auto exitButtonLabel = new UI::TextArea(translate("exit", "mainmenu"), 50, 20 + 41*5);
    exitButtonLabel->setFont(font4);
    exitButtonLabel->setWidth(150);
    exitButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    // Text areas
    addUI(introButtonLabel);
    addUI(newGameButtonLabel);
    addUI(loadGameButtonLabel);
    addUI(optionsButtonLabel);
    addUI(creditsButtonLabel);
    addUI(exitButtonLabel);
}

void MainMenu::doExit()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event::Event* event){ this->onExitStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doNewGame()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event::Event* event){ this->onNewGameStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doLoadGame()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event::Event* event){ this->onLoadGameStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doSettings()
{
    Game::getInstance()->pushState(new SettingsMenu());
}

void MainMenu::doIntro()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event::Event* event){ this->onIntroStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doCredits()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event::Event* event){ this->onCreditsStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::onExitButtonClick(Event::Mouse* event)
{
    doExit();
}

void MainMenu::onExitStart(Event::State* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->mixer()->stopMusic();
    Game::getInstance()->quit();
}

void MainMenu::onNewGameButtonClick(Event::Mouse* event)
{
    doNewGame();
}

void MainMenu::onNewGameStart(Event::State* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->pushState(new NewGame());
}

void MainMenu::onLoadGameButtonClick(Event::Mouse* event)
{
    doLoadGame();
}

void MainMenu::onLoadGameStart(Event::State* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->pushState(new LoadGame());
}

void MainMenu::onSettingsButtonClick(Event::Mouse* event)
{
    doSettings();
}

void MainMenu::onIntroButtonClick(Event::Mouse* event)
{
    doIntro();
}

void MainMenu::onIntroStart(Event::State* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->pushState(new Movie(17));
    Game::getInstance()->pushState(new Movie(1));
}

void MainMenu::onCreditsButtonClick(Event::Mouse* event)
{
    doCredits();
}

void MainMenu::onCreditsStart(Event::State* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->pushState(new Credits());
}

void MainMenu::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_e:
        case SDLK_ESCAPE:
            doExit();
            break;
        case SDLK_n:
            doNewGame();
            break;
        case SDLK_l:
            doLoadGame();
            break;
        case SDLK_i:
            doIntro();
            break;
        case SDLK_c:
            doCredits();
            break;
        case SDLK_o:
            doSettings();
            break;
    }
}

void MainMenu::onStateActivate(Event::State* event)
{
    Game::getInstance()->mixer()->playACMMusic("07desert.acm",true);
    Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
}

}
}
