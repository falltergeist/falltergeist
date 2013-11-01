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
#include "../States/PlayerEditAgeState.h"
#include "../Engine/Game.h"
#include "../Engine/Player.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/BigCounter.h"

// Third party includes

namespace Falltergeist
{


PlayerEditAgeState::PlayerEditAgeState(Game * game):State(game)
{

}

void PlayerEditAgeState::init()
{
    State::init();
    setFullscreen(false);

    Surface * bg = new Surface(_game->resourceManager()->surface("art/intrface/charwin.frm"));
    bg->setX(160);
    bg->setY(0);
    bg->setXOffset(0);
    bg->setYOffset(0);

    Surface * ageBox = new Surface(_game->resourceManager()->surface("art/intrface/agebox.frm"));
    ageBox->setX(168);
    ageBox->setY(10);
    ageBox->setXOffset(0);
    ageBox->setYOffset(0);

    Surface * doneBox = new Surface(_game->resourceManager()->surface("art/intrface/donebox.frm"));
    doneBox->setX(175);
    doneBox->setY(40);
    doneBox->setXOffset(0);
    doneBox->setYOffset(0);

    ImageButton * decButton = new ImageButton(ImageButton::TYPE_LEFT_ARROW, 178, 14);
    decButton->onLeftButtonClick((EventHandler) &PlayerEditAgeState::onDecButtonClick);

    ImageButton * incButton = new ImageButton(ImageButton::TYPE_RIGHT_ARROW, 262, 14);
    incButton->onLeftButtonClick((EventHandler) &PlayerEditAgeState::onIncButtonClick);

    ImageButton * doneButton= new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 188, 43);
    doneButton->onLeftButtonClick((EventHandler) &PlayerEditAgeState::onDoneButtonClick);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    TextArea * doneLabel = new TextArea(msg->message(100), 210, 43);
    doneLabel->setColor(0xffb89c28)->setFont("font3.aaf");

    _counter = new BigCounter(215, 13);
    _counter->setNumber(_game->player()->age());

    add(bg);
    add(ageBox);
    add(doneBox);
    add(incButton);
    add(decButton);
    add(doneLabel);
    add(doneButton);
    add(_counter);

}

PlayerEditAgeState::~PlayerEditAgeState()
{
    //delete _counter;
}

void PlayerEditAgeState::onDecButtonClick(Event * event)
{
    unsigned char age = _game->player()->age();
    if (age > 16)
    {
        age--;
        _game->player()->setAge(age);
        _counter->setNumber(age);
    }
}

void PlayerEditAgeState::onIncButtonClick(Event * event)
{
    unsigned char age = _game->player()->age();
    if (age < 35)
    {
        age++;
        _game->player()->setAge(age);
        _counter->setNumber(age);
    }
}

void PlayerEditAgeState::onDoneButtonClick(Event * event)
{
    _game->popState();
}


}
