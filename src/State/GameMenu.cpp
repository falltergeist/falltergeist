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

// Falltergeist includes
#include "../functions.h"
#include "../Audio/AudioMixer.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/GameMenu.h"
#include "../State/LoadGame.h"
#include "../State/Location.h"
#include "../State/SaveGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../Input/Mouse.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

GameMenu::GameMenu()
{
}

void GameMenu::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto background = new Image("art/intrface/opbase.frm");

    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;

    auto saveGameButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18);
    auto loadGameButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37);
    auto preferencesButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*2);
    auto exitGameButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*3);
    auto doneButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*4);

    preferencesButton->addEventHandler("mouseleftclick", [this](Event* event){ this->doPreferences(); });
    exitGameButton->addEventHandler("mouseleftclick",    [this](Event* event){ this->doExit(); });
    doneButton->addEventHandler("mouseleftclick",        [this](Event* event){ this->closeMenu(); });

    auto font = ResourceManager::font("font3.aaf", 0xb89c28ff);

    // label: save game
    auto saveGameButtonLabel = new TextArea(_t(MSG_OPTIONS, 0), backgroundX+8, backgroundY+26);
    saveGameButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    saveGameButton->addEventHandler("mouseleftclick", [this](Event* event){ this->doSaveGame(); });

    // label: load game
    auto loadGameButtonLabel = new TextArea(_t(MSG_OPTIONS, 1), backgroundX+8, backgroundY+26+37);
    loadGameButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    loadGameButton->addEventHandler("mouseleftclick", [this](Event* event){ this->doLoadGame(); });

    // label: preferences
    auto preferencesButtonLabel = new TextArea(_t(MSG_OPTIONS, 2), backgroundX+8, backgroundY+26+37*2);
    preferencesButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: exit game
    auto exitGameButtonLabel = new TextArea(_t(MSG_OPTIONS, 3), backgroundX+8, backgroundY+26+37*3);
    exitGameButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: done
    auto doneButtonLabel = new TextArea(_t(MSG_OPTIONS, 4), backgroundX+8, backgroundY+26+37*4);
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

void GameMenu::doSaveGame()
{
    Game::getInstance()->pushState(new SaveGame());
}

void GameMenu::doLoadGame()
{
    Game::getInstance()->pushState(new LoadGame());
}

void GameMenu::doPreferences()
{
    Game::getInstance()->pushState(new SettingsMenu());
}

void GameMenu::doExit()
{
    Game::getInstance()->pushState(new ExitConfirm());
}

void GameMenu::closeMenu()
{
    Game::getInstance()->popState();
}

void GameMenu::onStateActivate(StateEvent* event)
{
    Game::getInstance()->mouse()->pushState(Mouse::BIG_ARROW);
}

void GameMenu::onStateDeactivate(StateEvent* event)
{
    Game::getInstance()->mouse()->popState();
}

void GameMenu::onKeyDown(KeyboardEvent* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_d:
            closeMenu();
            break;
        case SDLK_s:
            doSaveGame();
            break;
        case SDLK_l:
            doLoadGame();
            break;
        case SDLK_p:
            doPreferences();
            break;
        case SDLK_e:
            doExit();
            break;
    }
}


}
}
