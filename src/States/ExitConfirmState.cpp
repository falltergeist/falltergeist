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
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../States/ExitConfirmState.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

ExitConfirmState::ExitConfirmState()
{
}

void ExitConfirmState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/lgdialog.frm"));

    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;

    auto box1 = std::shared_ptr<Image>(new Image("art/intrface/donebox.frm"));
    auto box2 = std::shared_ptr<Image>(new Image("art/intrface/donebox.frm"));
    box1->setX(backgroundX+38);
    box1->setY(backgroundY+98);
    box2->setX(backgroundX+170);
    box2->setY(backgroundY+98);

    auto yesButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+50, backgroundY+102));
    auto noButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+183, backgroundY+102));
    yesButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &ExitConfirmState::onYesButtonClick);
    noButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &ExitConfirmState::onNoButtonClick);

    // label: Are you sure you want to quit?
    auto msg = ResourceManager::msgFileType("text/english/game/misc.msg");
    auto font = ResourceManager::font("font1.aaf", 0xb89c28ff);
    auto quitLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(0), backgroundX+30, backgroundY+52));
    quitLabel->setFont(font)->setWidth(244)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: yes & no
    auto msg2 = ResourceManager::msgFileType("text/english/game/dbox.msg");
    auto fontBig = ResourceManager::font("font3.aaf", 0xb89c28ff);
    // label: yes 101
    auto yesButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg2->message(101), backgroundX+74, backgroundY+101));
    yesButtonLabel->setFont(fontBig);
    // label: no 102
    auto noButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg2->message(102), backgroundX+204, backgroundY+101));
    noButtonLabel->setFont(fontBig);

    background->setX(backgroundX);
    background->setY(backgroundY);

    add(background);
    add(box1);
    add(box2);
    add(yesButton);
    add(noButton);
    add(quitLabel);
    add(yesButtonLabel);
    add(noButtonLabel);
}

void ExitConfirmState::onYesButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->setState(std::shared_ptr<MainMenuState>(new MainMenuState()));
}

void ExitConfirmState::onNoButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

}
