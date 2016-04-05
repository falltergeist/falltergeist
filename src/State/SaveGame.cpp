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
#include "../State/SaveGame.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/State.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/ImageList.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        SaveGame::SaveGame() : State()
        {
        }

        SaveGame::~SaveGame()
        {
        }

        void SaveGame::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);

            auto game = Game::getInstance();
            //auto player = Game::getInstance()->player();

            // background
            auto bg = new UI::Image("art/intrface/lsgame.frm");
            Point bgPos = Point((game->renderer()->size() - bg->size()) / 2);
            int bgX = bgPos.x();
            int bgY = bgPos.y();
            bg->setPosition(bgPos);
            addUI(bg);

            // BUTTONS

            // button: up arrow
            addUI("button_up", new UI::ImageButton(UI::ImageButton::Type::SMALL_UP_ARROW, bgX+35, bgY+58));
            // button: down arrow
            addUI("button_down", new UI::ImageButton(UI::ImageButton::Type::SMALL_DOWN_ARROW, bgX+35, bgY+72));

            // button: Done
            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+391, bgY+349);
            doneButton->mouseClickHandler().add(std::bind(&SaveGame::onDoneButtonClick, this, std::placeholders::_1));
            addUI(doneButton);

            // button: Cancel
            auto cancelButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+495, bgY+349);
            cancelButton->mouseClickHandler().add(std::bind(&SaveGame::onCancelButtonClick, this, std::placeholders::_1));
            addUI(cancelButton);

            // LABELS
            std::string font3_907824ff = "font3.aaf";
            SDL_Color color = {0x90, 0x78, 0x24, 0xff};

            // SAVE GAME LABEL
            auto saveGameLabel = new UI::TextArea(_t(MSG_LOAD_SAVE, 109), bgX+48, bgY+27);
            saveGameLabel->setFont(font3_907824ff, color);
            addUI(saveGameLabel);

            // DONE BUTTON LABEL
            auto doneButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 300), bgX+410, bgY+348);
            doneButtonLabel->setFont(font3_907824ff, color);
            addUI(doneButtonLabel);

            // CANCEL BUTTON LABEL
            auto cancelButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 121), bgX+515, bgY+348);
            cancelButtonLabel->setFont(font3_907824ff, color);
            addUI(cancelButtonLabel);
        }

        void SaveGame::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void SaveGame::onCancelButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void SaveGame::onStateActivate(Event::State* event)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void SaveGame::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }

        void SaveGame::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    Game::getInstance()->popState();
                    break;
            }
        }
    }
}
