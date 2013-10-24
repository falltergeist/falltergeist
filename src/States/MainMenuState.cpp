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
#include <sstream>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Animation.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../States/MainMenuState.h"
#include "../States/SettingsMenuState.h"
#include "../States/NewGameState.h"

// Third party includes

namespace Falltergeist
{

MainMenuState::MainMenuState(Game * game) : State(game)
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init()
{
    State::init();
    _isFullscreen = true;
    // Background image
    Surface * background = new Surface(_game->resourceManager()->surface("art/intrface/mainmenu.frm"));
    background->setX(0);
    background->setY(0);
    background->setXOffset(0);
    background->setYOffset(0);

    // "Into" button
    ImageButton * introButton = new ImageButton(ImageButton::BUTTON_BIG_RED_CIRCLE, 29, 19);

    // "New game" button
    ImageButton * newGameButton = new ImageButton(ImageButton::BUTTON_BIG_RED_CIRCLE, 29, 19 + 41);
    newGameButton->onLeftButtonClick((EventHandler) &MainMenuState::onNewGameButtonClick);

    // "Load game" button
    ImageButton * loadGameButton = new ImageButton(ImageButton::BUTTON_BIG_RED_CIRCLE, 29, 19 + 41*2);

    // "Settings" button
    ImageButton * settingsButton = new ImageButton(ImageButton::BUTTON_BIG_RED_CIRCLE, 29, 19 + 41*3);
    settingsButton->onLeftButtonClick((EventHandler) &MainMenuState::onSettingsButtonClick);

    // "Credits" button
    ImageButton * creditsButton = new ImageButton(ImageButton::BUTTON_BIG_RED_CIRCLE, 29, 19 + 41*4);

    // "Exit" button
    ImageButton * exitButton = new ImageButton(ImageButton::BUTTON_BIG_RED_CIRCLE, 29, 19 + 41*5);
    exitButton->onLeftButtonClick((EventHandler) &MainMenuState::onExitButtonClick);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/misc.msg");

    // "Intro" label
    TextArea * introButtonLabel = new TextArea(msg->message(9), 55, 20);
    introButtonLabel->setColor(0xffb89c28)->setFont("font4.aaf")->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "New Game" label
    TextArea * newGameButtonLabel = new TextArea(msg->message(10), 50, 20 + 41);
    newGameButtonLabel->setColor(0xffb89c28)->setFont("font4.aaf")->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Load Game" label
    TextArea * loadGameButtonLabel = new TextArea(msg->message(11), 50, 20 + 41*2);
    loadGameButtonLabel->setColor(0xffb89c28)->setFont("font4.aaf")->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Options" label
    TextArea * optionsButtonLabel = new TextArea(msg->message(12), 50, 20 + 41*3);
    optionsButtonLabel->setColor(0xffb89c28)->setFont("font4.aaf")->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Credits" label
    TextArea * creditsButtonLabel = new TextArea(msg->message(13), 50, 20 + 41*4);
    creditsButtonLabel->setColor(0xffb89c28)->setFont("font4.aaf")->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Exit" label
    TextArea * exitButtonLabel = new TextArea(msg->message(14), 50, 20 + 41*5);
    exitButtonLabel->setColor(0xffb89c28)->setFont("font4.aaf")->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    add(background);
    // buttons
    add(introButton);
    add(newGameButton);
    add(loadGameButton);
    add(settingsButton);
    add(creditsButton);
    add(exitButton);
    // text areas
    add(introButtonLabel);
    add(newGameButtonLabel);
    add(loadGameButtonLabel);
    add(optionsButtonLabel);
    add(creditsButtonLabel);
    add(exitButtonLabel);
}

void MainMenuState::think()
{
}

void MainMenuState::onExitButtonClick()
{
    _game->quit();
}

void MainMenuState::onNewGameButtonClick()
{
    _game->pushState(new NewGameState(_game));
}

void MainMenuState::onSettingsButtonClick()
{
    //_game->pushState(new SettingsMenuState(_game));
}


}
