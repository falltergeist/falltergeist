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
    State::init();

    Game::getInstance()->mouse()->setType(Mouse::BIG_ARROW);

    // Background image
    auto background = std::shared_ptr<Image>(new Image("art/intrface/mainmenu.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // "Intro" button
    auto introButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, backgroundX+29, backgroundY+19));

    // "New game" button
    auto newGameButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, backgroundX+29, backgroundY+19 + 41));
    newGameButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod)&MainMenuState::onNewGameButtonClick);

    // "Load game" button
    auto loadGameButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, backgroundX+29, backgroundY+19 + 41*2));

    // "Settings" button
    auto settingsButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, backgroundX+29, backgroundY+19 + 41*3));
    settingsButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MainMenuState::onSettingsButtonClick);

    // "Credits" button
    auto creditsButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, backgroundX+29, backgroundY+19 + 41*4));

    // "Exit" button
    auto exitButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_MENU_RED_CIRCLE, backgroundX+29, backgroundY+19 + 41*5));
    exitButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MainMenuState::onExitButtonClick);


    auto msg = ResourceManager::msgFileType("text/english/game/misc.msg");

    auto font4 = ResourceManager::font("font4.aaf", 0xb89c28ff);

    // "Intro" label
    auto introButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(9), backgroundX+55, backgroundY+20));
    introButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "New Game" label
    auto newGameButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(10), backgroundX+50, backgroundY+20 + 41));
    newGameButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Load Game" label
    auto loadGameButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(11), backgroundX+50, backgroundY+20 + 41*2));
    loadGameButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Options" label
    auto optionsButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(12), backgroundX+50, backgroundY+20 + 41*3));
    optionsButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Credits" label
    auto creditsButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(13), backgroundX+50, backgroundY+20 + 41*4));
    creditsButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Exit" label
    auto exitButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(14), backgroundX+50, backgroundY+20 + 41*5));
    exitButtonLabel->setFont(font4)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // background
    addUI(background);

    // buttons
    addUI(introButton);

    addUI(newGameButton);
    addUI(loadGameButton);
    addUI(settingsButton);
    addUI(creditsButton);
    addUI(exitButton);

    // text areas
    addUI(introButtonLabel);
    addUI(newGameButtonLabel);
    addUI(loadGameButtonLabel);
    addUI(optionsButtonLabel);
    addUI(creditsButtonLabel);
    addUI(exitButtonLabel);
}

void MainMenuState::think()
{
    State::think();
}

void MainMenuState::onExitButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->quit();
}

void MainMenuState::onNewGameButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<NewGameState>(new NewGameState()));
}

void MainMenuState::onSettingsButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<SettingsMenuState>(new SettingsMenuState()));
}


}
