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
#include "../States/GameMenuState.h"
#include "../States/InventoryState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

InventoryState::InventoryState() : State()
{
}

InventoryState::~InventoryState()
{
}

void InventoryState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    // background
    auto background = std::shared_ptr<Image>(new Image("art/intrface/invbox.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5-50;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // buttons
    auto upButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_INVENTORY_UP_ARROW, backgroundX+128, backgroundY+40));
    auto downButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_INVENTORY_DOWN_ARROW, backgroundX+128, backgroundY+65));
    auto doneButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+438, backgroundY+328));

    // events
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &GameMenuState::onDoneButtonClick);

    add(background);
    add(upButton);
    add(downButton);
    add(doneButton);
}

void InventoryState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

}
