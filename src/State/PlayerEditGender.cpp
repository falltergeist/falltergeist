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
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Game/DudeObject.h"
#include "../State/PlayerEditGender.h"
#include "../UI/ImageList.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

PlayerEditGender::PlayerEditGender() : State()
{
}

void PlayerEditGender::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(true);

    auto bgX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto bgY = (Game::getInstance()->renderer()->height() - 480)*0.5;

    auto bg = new Image("art/intrface/charwin.frm");
    bg->setX(bgX+236);
    bg->setY(bgY+0);
    bg->addEventHandler("keydown", [this](Event* event){ this->onKeyPress(dynamic_cast<KeyboardEvent*>(event)); });

    _maleImage = new ImageList((std::vector<std::string>){
                                    "art/intrface/maleoff.frm",
                                    "art/intrface/maleon.frm"
                                }, bgX+260, bgY+2);
    _maleImage->addEventHandler("mouseleftclick", [this](Event* event){ this->onMaleButtonPress(dynamic_cast<MouseEvent*>(event)); });

    _femaleImage = new ImageList((std::vector<std::string>){
                                                            "art/intrface/femoff.frm",
                                                            "art/intrface/femon.frm"
                                                            }, bgX+310, bgY+2);
    _femaleImage->addEventHandler("mouseleftclick", [this](Event* event){ this->onFemaleButtonPress(dynamic_cast<MouseEvent*>(event)); });

    auto doneBox = new Image("art/intrface/donebox.frm");
    doneBox->setX(bgX+250);
    doneBox->setY(bgY+42);

    auto msg = ResourceManager::msgFileType("text/english/game/editor.msg");
    auto doneLabel = new TextArea(msg->message(100), bgX+281, bgY+45);
    auto font3_b89c28ff = ResourceManager::font("font3.aaf", 0xb89c28ff);
    doneLabel->setFont(font3_b89c28ff);

    auto doneButton = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, bgX+260, bgY+45);
    doneButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onDoneButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI(bg);
    addUI(doneBox);
    addUI(doneButton);
    addUI(doneLabel);
    addUI(_maleImage);
    addUI(_femaleImage);
    setGender(Game::getInstance()->player()->gender());
}

void PlayerEditGender::onDoneButtonClick(MouseEvent* event)
{
    Game::getInstance()->popState();
}

void PlayerEditGender::onFemaleButtonPress(MouseEvent* event)
{
    setGender(1); // 1 - female
}

void PlayerEditGender::onMaleButtonPress(MouseEvent* event)
{
    setGender(0); // 0 - male
}

void PlayerEditGender::onKeyPress(KeyboardEvent* event)
{
    switch (event->keyCode()) {
    case SDLK_ESCAPE:
        Game::getInstance()->popState();
        break;
    case SDLK_RETURN:
        Game::getInstance()->player()->setGender(_gender);
        Game::getInstance()->popState();
        break;
    case SDLK_LEFT:
    case SDLK_RIGHT:
        setGender(_gender ? 0 : 1);
        break;
    }
}

void PlayerEditGender::setGender(unsigned int gender)
{
    _gender = gender ? 1 : 0;
    _maleImage->setCurrentImage(gender ? 0 : 1);
    _femaleImage->setCurrentImage(gender ? 1 : 0);
}



}
}
