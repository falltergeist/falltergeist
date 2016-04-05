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
#include "../State/ExitConfirm.h"

// C++ standard includes

// Falltergeist includes
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../State/MainMenu.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/PlayerPanel.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        ExitConfirm::ExitConfirm() : State()
        {
        }

        ExitConfirm::~ExitConfirm()
        {
        }

        void ExitConfirm::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);

            auto background = new UI::Image("art/intrface/lgdialog.frm");
            auto panelHeight = Game::getInstance()->locationState()->playerPanel()->size().height();

            auto backgroundPos = (Game::getInstance()->renderer()->size() - background->size() - Point(0, panelHeight)) / 2;

            auto box1 = new UI::Image("art/intrface/donebox.frm");
            auto box2 = new UI::Image("art/intrface/donebox.frm");
            box1->setPosition(backgroundPos + Point(38, 98));
            box2->setPosition(backgroundPos + Point(170, 98));

            auto yesButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundPos + Point(50, 102));
            auto noButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundPos + Point(183, 102));
            yesButton->mouseClickHandler().add([this](Event::Event* event){ this->doYes(); });
            noButton->mouseClickHandler().add( [this](Event::Event* event){ this->doNo(); });

            // label: Are you sure you want to quit?
            auto quitLabel = new UI::TextArea(_t(MSG_MISC, 0), backgroundPos + Point(30, 52));
            quitLabel->setFont("font1.aaf", {0xb8,0x9c, 0x28, 0xff});
            quitLabel->setSize({244, 0});
            quitLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: yes & no
            // label: yes 101
            auto yesButtonLabel = new UI::TextArea(_t(MSG_DIALOG_BOX, 101), backgroundPos + Point(74, 101));
            yesButtonLabel->setFont("font3.aaf", {0xb8,0x9c,0x28,0xff});
            // label: no 102
            auto noButtonLabel = new UI::TextArea(_t(MSG_DIALOG_BOX, 102), backgroundPos + Point(204, 101));
            noButtonLabel->setFont("font3.aaf", {0xb8,0x9c,0x28,0xff});

            background->setPosition(backgroundPos);

            addUI(background);
            addUI(box1);
            addUI(box2);
            addUI(yesButton);
            addUI(noButton);
            addUI(quitLabel);
            addUI(yesButtonLabel);
            addUI(noButtonLabel);
        }

        void ExitConfirm::doYes()
        {
            Game::getInstance()->setState(new MainMenu());
        }

        void ExitConfirm::doNo()
        {
            Game::getInstance()->popState();
        }

        void ExitConfirm::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_n:
                    doNo();
                    break;
                case SDLK_RETURN:
                case SDLK_y:
                    doYes();
                    break;
            }
        }

        void ExitConfirm::onStateActivate(Event::State* event)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void ExitConfirm::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }
    }
}
