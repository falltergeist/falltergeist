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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../States/PlayerEditAlertState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

PlayerEditAlertState::PlayerEditAlertState() : State()
{
}

PlayerEditAlertState::~PlayerEditAlertState()
{
}

void PlayerEditAlertState::setMessage(std::string message)
{
    _message = message;
}

void PlayerEditAlertState::init()
{
    State::init();
    setFullscreen(false);
    setModal(true);

    auto bg = new Image("art/intrface/lgdialog.frm");

    auto bgX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto bgY = (Game::getInstance()->renderer()->height() - 480)*0.5;

    bg->setX(bgX+164);
    bg->setY(bgY+173);

    auto font1_ff9f48ff = ResourceManager::font("font1.aaf", 0xff9f48ff);

    auto message = new TextArea(_message.c_str(), bgX+194, bgY+213);
    message->setWidth(250);
    message->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    message->setFont(font1_ff9f48ff);

    auto doneBox = new Image("art/intrface/donebox.frm");
    doneBox->setX(bgX+254);
    doneBox->setY(bgY+270);

    auto doneButton = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, bgX+264, bgY+273);
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAlertState::onDoneButtonClick);

    auto msg = ResourceManager::msgFileType("text/english/game/editor.msg");
    auto doneLabel = new TextArea(msg->message(100), bgX+284, bgY+273);
    auto font3_b89c28ff = ResourceManager::font("font3.aaf", 0xb89c28ff);
    doneLabel->setFont(font3_b89c28ff);

    addUI(bg);
    addUI(message);
    addUI(doneBox);
    addUI(doneButton);
    addUI(doneLabel);
}

void PlayerEditAlertState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

}
