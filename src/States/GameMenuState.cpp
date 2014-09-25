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

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../States/ExitConfirmState.h"
#include "../States/GameMenuState.h"
#include "../States/LocationState.h"
#include "../States/SettingsMenuState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

GameMenuState::GameMenuState()
{
}

void GameMenuState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/opbase.frm"));

    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;

    auto saveGameButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18));
    auto loadGameButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37));
    auto preferencesButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*2));
    auto exitGameButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*3));
    auto doneButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*4));

    preferencesButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &GameMenuState::onPreferencesButtonClick);
    exitGameButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &GameMenuState::onExitButtonClick);
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &GameMenuState::onDoneButtonClick);


    auto msg = ResourceManager::msgFileType("text/english/game/options.msg");
    auto font = ResourceManager::font("font3.aaf", 0xb89c28ff);

    // label: save game
    auto saveGameButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(0), backgroundX+8, backgroundY+26));
    saveGameButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: load game
    auto loadGameButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(1), backgroundX+8, backgroundY+26+37));
    loadGameButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: preferences
    auto preferencesButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(2), backgroundX+8, backgroundY+26+37*2));
    preferencesButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: exit game
    auto exitGameButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(3), backgroundX+8, backgroundY+26+37*3));
    exitGameButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: done
    auto doneButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(4), backgroundX+8, backgroundY+26+37*4));
    doneButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    background->setX(backgroundX);
    background->setY(backgroundY);

    addUI(background);
    addUI(saveGameButton);
    addUI(loadGameButton);
    addUI(preferencesButton);
    addUI(exitGameButton);
    addUI(doneButton);
    addUI(saveGameButtonLabel);
    addUI(loadGameButtonLabel);
    addUI(preferencesButtonLabel);
    addUI(exitGameButtonLabel);
    addUI(doneButtonLabel);
}

void GameMenuState::onPreferencesButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(new SettingsMenuState());
}

void GameMenuState::onExitButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(new ExitConfirmState());
}

void GameMenuState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

}
