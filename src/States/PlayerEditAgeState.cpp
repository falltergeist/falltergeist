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
#include "../States/PlayerEditAgeState.h"
#include "../Engine/Game.h"
#include "../Game/GameDudeObject.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/BigCounter.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{


PlayerEditAgeState::PlayerEditAgeState():State()
{

}

void PlayerEditAgeState::init()
{
    State::init();
    setFullscreen(false);

    auto bg = std::shared_ptr<Image>(new Image("art/intrface/charwin.frm"));
    bg->setX(160);
    bg->setY(0);

    auto ageBox = std::shared_ptr<Image>(new Image("art/intrface/agebox.frm"));
    ageBox->setX(168);
    ageBox->setY(10);

    auto doneBox = std::shared_ptr<Image>(new Image("art/intrface/donebox.frm"));
    doneBox->setX(175);
    doneBox->setY(40);

    auto decButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_LEFT_ARROW, 178, 14));
    decButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAgeState::onDecButtonClick);

    auto incButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_RIGHT_ARROW, 262, 14));
    incButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAgeState::onIncButtonClick);

    auto doneButton= std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 188, 43));
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAgeState::onDoneButtonClick);

    auto msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    auto doneLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(100), 210, 43));

    auto font3_b89c28ff = _game->resourceManager()->font("font3.aaf", 0xb89c28ff);

    doneLabel->setFont(font3_b89c28ff);

    _counter = std::shared_ptr<BigCounter>(new BigCounter(215, 13));
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
}

void PlayerEditAgeState::onDecButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto state = dynamic_cast<PlayerEditAgeState*>(event->reciever());
    unsigned char age = Game::getInstance()->player()->age();
    if (age > 16)
    {
        age--;
        Game::getInstance()->player()->setAge(age);
        state->_counter->setNumber(age);
    }
}

void PlayerEditAgeState::onIncButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto state = dynamic_cast<PlayerEditAgeState*>(event->reciever());
    unsigned char age = Game::getInstance()->player()->age();
    if (age < 35)
    {
        age++;
        Game::getInstance()->player()->setAge(age);
        state->_counter->setNumber(age);
    }
}

void PlayerEditAgeState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}


}
