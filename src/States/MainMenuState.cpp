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

#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Animation.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../States/MainMenuState.h"
#include "../States/NewGameState.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

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
    add(_game->resourceManager()->surface("art/intrface/mainmenu.frm"));

    // "Into" button
    ImageButton * introButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19);

    // "New game" button
    ImageButton * newGameButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41);
    newGameButton->onLeftButtonClick((EventHandler) &MainMenuState::onNewGameButtonClick);

    // "Load game" button
    ImageButton * loadGameButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*2);

    // "Settings" button
    ImageButton * settingsButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*3);

    // "Credits" button
    ImageButton * creditsButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*4);

    // "Exit" button
    ImageButton * exitButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*5);
    exitButton->onLeftButtonClick((EventHandler) &MainMenuState::onExitButtonClick);

    // "Intro" label
    TextArea * introButtonLabel = new TextArea("INTRO", 55, 20);
    introButtonLabel->setColor(0xffb89c28);
    introButtonLabel->setFont("font4.aaf");
    introButtonLabel->setWidth(140);
    introButtonLabel->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "New Game" label
    TextArea * newGameButtonLabel = new TextArea("NEW GAME", 55, 20 + 41);
    newGameButtonLabel->setColor(0xffb89c28);
    newGameButtonLabel->setFont("font4.aaf");
    newGameButtonLabel->setWidth(140);
    newGameButtonLabel->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Load Game" label
    TextArea * loadGameButtonLabel = new TextArea("LOAD GAME", 55, 20 + 41*2);
    loadGameButtonLabel->setColor(0xffb89c28);
    loadGameButtonLabel->setFont("font4.aaf");
    loadGameButtonLabel->setWidth(140);
    loadGameButtonLabel->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Options" label
    TextArea * optionsButtonLabel = new TextArea("OPTIONS", 55, 20 + 41*3);
    optionsButtonLabel->setColor(0xffb89c28);
    optionsButtonLabel->setFont("font4.aaf");
    optionsButtonLabel->setWidth(140);
    optionsButtonLabel->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Credits" label
    TextArea * creditsButtonLabel = new TextArea("CREDITS", 55, 20 + 41*4);
    creditsButtonLabel->setColor(0xffb89c28);
    creditsButtonLabel->setFont("font4.aaf");
    creditsButtonLabel->setWidth(140);
    creditsButtonLabel->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // "Exit" label
    TextArea * exitButtonLabel = new TextArea("EXIT", 55, 20 + 41*5);
    exitButtonLabel->setColor(0xffb89c28);
    exitButtonLabel->setFont("font4.aaf");
    exitButtonLabel->setWidth(140);
    exitButtonLabel->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

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

}
