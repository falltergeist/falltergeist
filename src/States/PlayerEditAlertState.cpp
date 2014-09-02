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
#include "../States/PlayerEditAlertState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"

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

    auto bg = new Image("art/intrface/lgdialog.frm");
    bg->setX(164);
    bg->setY(173);

    auto font1_ff9f48ff = _game->resourceManager()->font("font1.aaf", 0xff9f48ff);

    TextArea * message = new TextArea(_message.c_str(), 194, 213);
    message->setWidth(250);
    message->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    message->setFont(font1_ff9f48ff);

    auto doneBox = new Image("art/intrface/donebox.frm");
    doneBox->setX(254);
    doneBox->setY(270);

    ImageButton * doneButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 264, 273);
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAlertState::onDoneButtonClick);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    TextArea * doneLabel = new TextArea(msg->message(100), 284, 273);

    auto font3_b89c28ff = _game->resourceManager()->font("font3.aaf", 0xb89c28ff);

    doneLabel->setFont(font3_b89c28ff);

    add(bg);
    add(message);
    add(doneBox);
    add(doneButton);
    add(doneLabel);
}

void PlayerEditAlertState::onDoneButtonClick(MouseEvent* event)
{
    _game->popState();
}

}
