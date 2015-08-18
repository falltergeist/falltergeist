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
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../State/PlayerEditAlert.h"
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

    auto bgX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto bgY = (Game::getInstance()->renderer()->height() - 480)*0.5;

    bg->setX(bgX+164);
    bg->setY(bgY+173);

    auto font1_ff9f48ff = ResourceManager::getInstance()->font("font1.aaf", 0xff9f48ff);

    auto message = new UI::TextArea(_message.c_str(), bgX+194, bgY+213);
    message->setWidth(250);
    message->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
    message->setFont(font1_ff9f48ff);

    auto doneBox = new UI::Image("art/intrface/donebox.frm");
    doneBox->setX(bgX+254);
    doneBox->setY(bgY+270);

    auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+264, bgY+273);
    doneButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onDoneButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX+284, bgY+273);
    auto font3_b89c28ff = ResourceManager::getInstance()->font("font3.aaf", 0xb89c28ff);
    doneLabel->setFont(font3_b89c28ff);

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
