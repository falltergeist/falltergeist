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
#include "../State/GameMenu.h"

// C++ standard includes

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/LoadGame.h"
#include "../State/Location.h"
#include "../State/SaveGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/PlayerPanel.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        GameMenu::GameMenu() : State()
        {
        }

        GameMenu::~GameMenu()
        {
        }

        void GameMenu::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);

            auto background = new UI::Image("art/intrface/opbase.frm");
            auto panelHeight = Game::getInstance()->locationState()->playerPanel()->size().height();

            auto backgroundPos = (Game::getInstance()->renderer()->size() - background->size() - Point(0, panelHeight)) / 2;
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();

            auto saveGameButton    = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18);
            auto loadGameButton    = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37);
            auto preferencesButton = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*2);
            auto exitGameButton    = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*3);
            auto doneButton        = new UI::ImageButton(UI::ImageButton::Type::OPTIONS_BUTTON, backgroundX+14, backgroundY+18+37*4);

            preferencesButton->mouseClickHandler().add([this](Event::Event* event){ this->doPreferences(); });
            exitGameButton->mouseClickHandler().add(   [this](Event::Event* event){ this->doExit(); });
            doneButton->mouseClickHandler().add(       [this](Event::Event* event){ this->closeMenu(); });

            auto font = ResourceManager::getInstance()->font("font3.aaf");
            SDL_Color color = {0xb8, 0x9c, 0x28, 0xff};

            // label: save game
            auto saveGameButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 0), backgroundX+8, backgroundY+26);
            saveGameButtonLabel->setFont(font, color);
            saveGameButtonLabel->setSize({150, 0});
            saveGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            saveGameButton->mouseClickHandler().add([this](Event::Event* event){ this->doSaveGame(); });

            // label: load game
            auto loadGameButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 1), backgroundX+8, backgroundY+26+37);
            loadGameButtonLabel->setFont(font, color);
            loadGameButtonLabel->setSize({150, 0});
            loadGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            loadGameButton->mouseClickHandler().add([this](Event::Event* event){ this->doLoadGame(); });

            // label: preferences
            auto preferencesButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 2), backgroundX+8, backgroundY+26+37*2);
            preferencesButtonLabel->setFont(font, color);
            preferencesButtonLabel->setSize({150, 0});
            preferencesButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: exit game
            auto exitGameButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 3), backgroundX+8, backgroundY+26+37*3);
            exitGameButtonLabel->setFont(font, color);
            exitGameButtonLabel->setSize({150, 0});
            exitGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: done
            auto doneButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 4), backgroundX+8, backgroundY+26+37*4);
            doneButtonLabel->setFont(font, color);
            doneButtonLabel->setSize({150, 0});
            doneButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            background->setPosition(backgroundPos);

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

        void GameMenu::onStateActivate(Event::State* event)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void GameMenu::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }

        void GameMenu::onKeyDown(Event::Keyboard* event)
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
