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
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../States/MainMenuState.h"
#include "../States/NewGameState.h"
#include "../States/SettingsMenuState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

MainMenuState::MainMenuState() : State()
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init()
{
    if (_initialized) return;
    State::init();

    Game::getInstance()->mouse()->setType(Mouse::BIG_ARROW);

    auto renderer = Game::getInstance()->renderer();
    setX((renderer->width()  - 640)*0.5);
    setY((renderer->height() - 480)*0.5);

    addUI("background", new Image("art/intrface/mainmenu.frm"));

    addUI("intro_button", new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, 29, 19));

    auto newGameButton = addUI(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, 29, 19 + 41));
    newGameButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod)&MainMenuState::onNewGameButtonClick);

    addUI("loadgame_button", new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, 29, 19 + 41*2));

    auto settingsButton = addUI(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, 29, 19 + 41*3));
    settingsButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MainMenuState::onSettingsButtonClick);

    addUI("credits_button", new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, 29, 19 + 41*4));

    auto exitButton = addUI(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, 29, 19 + 41*5));
    exitButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MainMenuState::onExitButtonClick);

    auto msg = ResourceManager::msgFileType("text/english/game/misc.msg");
    auto font4 = ResourceManager::font("font4.aaf", 0xb89c28ff);

    // "Intro" label
    auto introButtonLabel = new TextArea(msg->message(9), 50, 20);
    introButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "New Game" label
    auto newGameButtonLabel = new TextArea(msg->message(10), 50, 20 + 41);
    newGameButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Load Game" label
    auto loadGameButtonLabel = new TextArea(msg->message(11), 50, 20 + 41*2);
    loadGameButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Options" label
    auto optionsButtonLabel = new TextArea(msg->message(12), 50, 20 + 41*3);
    optionsButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Credits" label
    auto creditsButtonLabel = new TextArea(msg->message(13), 50, 20 + 41*4);
    creditsButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Exit" label
    auto exitButtonLabel = new TextArea(msg->message(14), 50, 20 + 41*5);
    exitButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // Text areas
    addUI(introButtonLabel);
    addUI(newGameButtonLabel);
    addUI(loadGameButtonLabel);
    addUI(optionsButtonLabel);
    addUI(creditsButtonLabel);
    addUI(exitButtonLabel);
}

void MainMenuState::onExitButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->quit();
}

void MainMenuState::onNewGameButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(new NewGameState());
}

void MainMenuState::onSettingsButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(new SettingsMenuState());
}

}
