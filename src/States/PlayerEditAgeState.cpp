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
#include "../Game/GameDudeObject.h"
#include "../States/PlayerEditAgeState.h"
#include "../UI/BigCounter.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

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
    setModal(true);

    auto backgroundX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - 480)*0.5;

    auto bg = std::shared_ptr<Image>(new Image("art/intrface/charwin.frm"));
    bg->setX(backgroundX+160);
    bg->setY(backgroundY+0);

    auto ageBox = std::shared_ptr<Image>(new Image("art/intrface/agebox.frm"));
    ageBox->setX(backgroundX+168);
    ageBox->setY(backgroundY+10);

    auto doneBox = std::shared_ptr<Image>(new Image("art/intrface/donebox.frm"));
    doneBox->setX(backgroundX+175);
    doneBox->setY(backgroundY+40);

    auto decButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_LEFT_ARROW, backgroundX+178, backgroundY+14));
    decButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAgeState::onDecButtonClick);

    auto incButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_RIGHT_ARROW, backgroundX+262, backgroundY+14));
    incButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAgeState::onIncButtonClick);

    auto doneButton= std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+188, backgroundY+43));
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerEditAgeState::onDoneButtonClick);

    auto msg = ResourceManager::msgFileType("text/english/game/editor.msg");
    auto doneLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(100), backgroundX+210, backgroundY+43));

    auto font3_b89c28ff = ResourceManager::font("font3.aaf", 0xb89c28ff);

    doneLabel->setFont(font3_b89c28ff);

    _counter = std::shared_ptr<BigCounter>(new BigCounter(backgroundX+215, backgroundY+13));
    _counter->setNumber(Game::getInstance()->player()->age());

    addUI(bg);
    addUI(ageBox);
    addUI(doneBox);
    addUI(incButton);
    addUI(decButton);
    addUI(doneLabel);
    addUI(doneButton);
    addUI(_counter);

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
