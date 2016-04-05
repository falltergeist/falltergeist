/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../State/PlayerCreateOptions.h"

// C++ standard includes

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/LoadGame.h"
#include "../State/Location.h"
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
        PlayerCreateOptions::PlayerCreateOptions() : State()
        {
        }

        PlayerCreateOptions::~PlayerCreateOptions()
        {
        }

        void PlayerCreateOptions::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);

            auto background = new UI::Image("art/intrface/opbase.frm");

            Point backgroundPos = Point((Game::getInstance()->renderer()->size() - background->size()) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();

            auto saveButton = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18);
            auto loadButton = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37);
            auto printToFileButton = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*2);
            auto eraseButton = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*3);
            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*4);

            saveButton->mouseClickHandler().add(   std::bind(&PlayerCreateOptions::onSaveButtonClick, this, std::placeholders::_1));
            loadButton->mouseClickHandler().add(   std::bind(&PlayerCreateOptions::onLoadButtonClick, this, std::placeholders::_1));
            printToFileButton->mouseClickHandler().add(std::bind(&PlayerCreateOptions::onPrintToFileButtonClick, this, std::placeholders::_1));
            eraseButton->mouseClickHandler().add(      std::bind(&PlayerCreateOptions::onEraseButtonClick, this, std::placeholders::_1));
            doneButton->mouseClickHandler().add(       std::bind(&PlayerCreateOptions::onDoneButtonClick, this, std::placeholders::_1));

            auto font = ResourceManager::getInstance()->font("font3.aaf");
            SDL_Color color = {0xb8, 0x9c, 0x28, 0xff};

            // label: save
            auto saveButtonLabel = new UI::TextArea(_t(MSG_EDITOR, 600), backgroundX+8, backgroundY+26);
            saveButtonLabel->setFont(font, color);
            saveButtonLabel->setWidth(150);
            saveButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: load
            auto loadButtonLabel = new UI::TextArea(_t(MSG_EDITOR, 601), backgroundX+8, backgroundY+26+37);
            loadButtonLabel->setFont(font, color);
            loadButtonLabel->setWidth(150);
            loadButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: print to file
            auto printToFileButtonLabel = new UI::TextArea(_t(MSG_EDITOR, 602), backgroundX+8, backgroundY+26+37*2);
            printToFileButtonLabel->setFont(font, color);
            printToFileButtonLabel->setWidth(150);
            printToFileButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: erase
            auto eraseButtonLabel = new UI::TextArea(_t(MSG_EDITOR, 603), backgroundX+8, backgroundY+26+37*3);
            eraseButtonLabel->setFont(font, color);
            eraseButtonLabel->setWidth(150);
            eraseButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: done
            auto doneButtonLabel = new UI::TextArea(_t(MSG_EDITOR, 604), backgroundX+8, backgroundY+26+37*4);
            doneButtonLabel->setFont(font, color);
            doneButtonLabel->setWidth(150);
            doneButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            background->setPosition(backgroundPos);

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

        void PlayerCreateOptions::onSaveButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new SavePlayerStatState());
        }

        void PlayerCreateOptions::onLoadButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new LoadPlayerStatState());
        }

        void PlayerCreateOptions::onPrintToFileButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new SettingsMenu());
        }

        void PlayerCreateOptions::onEraseButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new EraseConfirmState());
        }

        void PlayerCreateOptions::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void PlayerCreateOptions::onKeyDown(Event::Keyboard* event)
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
