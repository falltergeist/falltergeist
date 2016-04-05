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
#include "../State/PlayerEditAlert.h"

// C++ standard includes

// Falltergeist includes
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        PlayerEditAlert::PlayerEditAlert() : State()
        {
        }

        PlayerEditAlert::~PlayerEditAlert()
        {
        }

        void PlayerEditAlert::setMessage(const std::string& message)
        {
            _message = message;
        }

        void PlayerEditAlert::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(true);

            auto bg = new UI::Image("art/intrface/lgdialog.frm");

            Point bgPos = Point((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
            int bgX = bgPos.x();
            int bgY = bgPos.y();

            bg->setPosition(bgPos + Point(164, 173));


            auto message = new UI::TextArea(_message.c_str(), bgPos + Point(194, 213));
            message->setWidth(250);
            message->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            message->setFont("font1.aaf", {0xff, 0x9f, 0x48, 0xff});

            auto doneBox = new UI::Image("art/intrface/donebox.frm");
            doneBox->setPosition(bgPos + Point(254, 270));

            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX + 264, bgY + 273);
            doneButton->mouseClickHandler().add([this](Event::Mouse* event)
            {
                this->onDoneButtonClick(event);
            });

            auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX + 284, bgY + 273);
            doneLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            addUI(bg);
            addUI(message);
            addUI(doneBox);
            addUI(doneButton);
            addUI(doneLabel);
        }

        void PlayerEditAlert::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }
    }
}
