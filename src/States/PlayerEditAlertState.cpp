/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include "../Engine/Surface.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{

PlayerEditAlertState::PlayerEditAlertState(Game * game) : State(game)
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

    Surface * bg = new Surface(_game->resourceManager()->surface("art/intrface/lgdialog.frm"));
    bg->setX(164);
    bg->setY(173);
    bg->setXOffset(0);
    bg->setYOffset(0);

    TextArea * message = new TextArea(_message.c_str(), 194, 213);
    message->setWidth(250);
    message->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    message->setColor(0xFFFF9F48);

    Surface * doneBox = new Surface(_game->resourceManager()->surface("art/intrface/donebox.frm"));
    doneBox->setX(254);
    doneBox->setY(270);
    doneBox->setXOffset(0);
    doneBox->setYOffset(0);

    ImageButton * doneButton= new ImageButton(ImageButton::BUTTON_SMALL_RED_CIRCLE, 264, 273);
    doneButton->onLeftButtonClick((EventHandler) &PlayerEditAlertState::onDoneButtonClick);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    TextArea * doneLabel = new TextArea(msg->message(100), 284, 273);
    doneLabel->setColor(0xffb89c28)->setFont("font3.aaf");

    add(bg);
    add(message);
    add(doneBox);
    add(doneButton);
    add(doneLabel);
}

void PlayerEditAlertState::onDoneButtonClick(Event * event)
{
    _game->popState();
}

}
