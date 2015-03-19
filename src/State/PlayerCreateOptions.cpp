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
#include "../Audio/AudioMixer.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/LoadGame.h"
#include "../State/Location.h"
#include "../State/PlayerCreateOptions.h"
#include "../State/SaveGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

PlayerCreateOptions::PlayerCreateOptions()
{
}

void PlayerCreateOptions::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto background = new Image("art/intrface/opbase.frm");

    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;

    auto saveButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18);
    auto loadButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37);
    auto printToFileButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*2);
    auto eraseButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*3);
    auto doneButton = new ImageButton(ImageButton::TYPE_OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*4);

    saveButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onSaveButtonClick(dynamic_cast<MouseEvent*>(event)); });
    loadButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onLoadButtonClick(dynamic_cast<MouseEvent*>(event)); });
    printToFileButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onPrintToFileButtonClick(dynamic_cast<MouseEvent*>(event)); });
    eraseButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onEraseButtonClick(dynamic_cast<MouseEvent*>(event)); });
    doneButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onDoneButtonClick(dynamic_cast<MouseEvent*>(event)); });

    auto font = ResourceManager::font("font3.aaf", 0xb89c28ff);

    // label: save
    auto saveButtonLabel = new TextArea(_t(MSG_EDITOR, 600), backgroundX+8, backgroundY+26);
    saveButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: load
    auto loadButtonLabel = new TextArea(_t(MSG_EDITOR, 601), backgroundX+8, backgroundY+26+37);
    loadButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: print to file
    auto printToFileButtonLabel = new TextArea(_t(MSG_EDITOR, 602), backgroundX+8, backgroundY+26+37*2);
    printToFileButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: erase
    auto eraseButtonLabel = new TextArea(_t(MSG_EDITOR, 603), backgroundX+8, backgroundY+26+37*3);
    eraseButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: done
    auto doneButtonLabel = new TextArea(_t(MSG_EDITOR, 604), backgroundX+8, backgroundY+26+37*4);
    doneButtonLabel->setFont(font)->setWidth(150)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    background->setX(backgroundX);
    background->setY(backgroundY);

    addUI(background);

    addUI(saveButton);
    addUI(loadButton);
    addUI(printToFileButton);
    addUI(eraseButton);
    addUI(doneButton);

    addUI(saveButtonLabel);
    addUI(loadButtonLabel);
    addUI(printToFileButtonLabel);
    addUI(eraseButtonLabel);
    addUI(doneButtonLabel);
}

void PlayerCreateOptions::onSaveButtonClick(MouseEvent* event)
{
//    Game::getInstance()->pushState(new SavePlayerStatState());
}

void PlayerCreateOptions::onLoadButtonClick(MouseEvent* event)
{
//    Game::getInstance()->pushState(new LoadPlayerStatState());
}

void PlayerCreateOptions::onPrintToFileButtonClick(MouseEvent* event)
{
//    Game::getInstance()->pushState(new SettingsMenu());
}

void PlayerCreateOptions::onEraseButtonClick(MouseEvent* event)
{
//    Game::getInstance()->pushState(new EraseConfirmState());
}

void PlayerCreateOptions::onDoneButtonClick(MouseEvent* event)
{
    Game::getInstance()->popState();
}

void PlayerCreateOptions::onKeyDown(KeyboardEvent* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_RETURN:
        case SDLK_d:
            Game::getInstance()->popState();
            break;
    }
}

}
}
