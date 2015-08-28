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
#include "../Game/DudeObject.h"
#include "../State/PlayerEditAge.h"
#include "../UI/BigCounter.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

PlayerEditAge::PlayerEditAge() : State()
{
}

PlayerEditAge::~PlayerEditAge()
{
}

void PlayerEditAge::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(true);

    auto backgroundX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - 480)*0.5;

    auto bg = std::make_shared<UI::Image>("art/intrface/charwin.frm");
    bg->setX(backgroundX+160);
    bg->setY(backgroundY+0);

    auto ageBox = std::make_shared<UI::Image>("art/intrface/agebox.frm");
    ageBox->setX(backgroundX+168);
    ageBox->setY(backgroundY+10);

    auto doneBox = std::make_shared<UI::Image>("art/intrface/donebox.frm");
    doneBox->setX(backgroundX+175);
    doneBox->setY(backgroundY+40);

    auto decButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::LEFT_ARROW, backgroundX+178, backgroundY+14);
    decButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onDecButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    auto incButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::RIGHT_ARROW, backgroundX+262, backgroundY+14);
    incButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onIncButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    auto doneButton= std::make_shared<UI::ImageButton>(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+188, backgroundY+43);
    doneButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onDoneButtonClick(dynamic_cast<Event::Mouse*>(event)); });

    auto doneLabel = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 100), backgroundX+210, backgroundY+43);

    auto font3_b89c28ff = ResourceManager::getInstance()->font("font3.aaf", 0xb89c28ff);

    doneLabel->setFont(font3_b89c28ff);

    _counter = std::make_shared<UI::BigCounter>(backgroundX+215, backgroundY+13);
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

void PlayerEditAge::onDecButtonClick(Event::Mouse* event)
{
    doDec();
}

void PlayerEditAge::onIncButtonClick(Event::Mouse* event)
{
    doInc();
}

void PlayerEditAge::onDoneButtonClick(Event::Mouse* event)
{
    doDone();
}

void PlayerEditAge::doBack()
{
    Game::getInstance()->popState();
}

void PlayerEditAge::doDec()
{
    unsigned char age = _counter->number();
    if (age > 16)
    {
        age--;
        _counter->setNumber(age);
    }
}

void PlayerEditAge::doDone()
{
    Game::getInstance()->player()->setAge(_counter->number());
    Game::getInstance()->popState();
}

void PlayerEditAge::doInc()
{
    unsigned char age = _counter->number();
    if (age < 35)
    {
        age++;
        _counter->setNumber(age);
    }
}

void PlayerEditAge::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_RIGHT:
            doInc();
            break;
        case SDLK_LEFT:
            doDec();
            break;
        case SDLK_ESCAPE:
            doBack();
            break;
        case SDLK_RETURN:
            doDone();
            break;
    }
}


}
}
