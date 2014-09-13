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
#include "../States/SkilldexState.h"
#include "../States/LocationState.h"
#include "../States/SettingsMenuState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

SkilldexState::SkilldexState()
{
}

void SkilldexState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    // original coordinates = 455x6
    // background size = 185x368
    auto background = std::shared_ptr<Image>(new Image("art/intrface/skldxbox.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() + 640 - 2*background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - 480 + 6);
    background->setX(backgroundX);
    background->setY(backgroundY);

    // buttons
    auto sneakButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44));
    auto lockpickButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36));
    auto stealButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36*2));
    auto trapsButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36*3));
    auto firstAidButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36*4));
    auto doctorButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36*5));
    auto scienceButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36*6));
    auto repairButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SKILLDEX_BUTTON, backgroundX+14, backgroundY+44+36*7));
    auto cancelButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+48, backgroundY+338));

    // events
    cancelButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &SkilldexState::onCancelButtonClick);

    // LABELS
    auto msg = ResourceManager::msgFileType("text/english/game/skilldex.msg");
    auto font = ResourceManager::font("font3.aaf", 0xb89c28ff);

    // label: skilldex (100)
    auto skilldexLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(100), backgroundX+56, backgroundY+14));
    skilldexLabel->setFont(font)->setWidth(76)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: sneak (102)
    auto sneakLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(102), backgroundX+17, backgroundY+52));
    sneakLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: lockpick (103)
    auto lockpickLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(103), backgroundX+17, backgroundY+52+36));
    lockpickLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: steal (104)
    auto stealLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(104), backgroundX+17, backgroundY+52+36*2));
    stealLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: traps (105)
    auto trapsLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(105), backgroundX+17, backgroundY+52+36*3));
    trapsLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: first aid (106)
    auto firstAidLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(106), backgroundX+17, backgroundY+52+36*4));
    firstAidLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: doctor (107)
    auto doctorLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(107), backgroundX+17, backgroundY+52+36*5));
    doctorLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: science (108)
    auto scienceLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(108), backgroundX+17, backgroundY+52+36*6));
    scienceLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    // label: repair (109)
    auto repairLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(109), backgroundX+17, backgroundY+52+36*7));
    repairLabel->setFont(font)->setWidth(84)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    // label: cancel (101)
    auto cancelButtonLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(101), backgroundX+70, backgroundY+337));
    cancelButtonLabel->setFont(font);

    // add all buttons and labels
    add(background);
    add(sneakButton);
    add(lockpickButton);
    add(stealButton);
    add(trapsButton);
    add(firstAidButton);
    add(doctorButton);
    add(scienceButton);
    add(repairButton);
    add(cancelButton);
    add(skilldexLabel);
    add(sneakLabel);
    add(lockpickLabel);
    add(stealLabel);
    add(trapsLabel);
    add(firstAidLabel);
    add(doctorLabel);
    add(scienceLabel);
    add(repairLabel);
    add(cancelButtonLabel);
}

void SkilldexState::onCancelButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

}
