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
#include "../States/PipBoyState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{

PipBoyState::PipBoyState() : State()
{
}

PipBoyState::~PipBoyState()
{
}

void PipBoyState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    // background
    auto background = std::shared_ptr<Image>(new Image("art/intrface/pip.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Close button
    auto closeButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+448));
    closeButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PipBoyState::onCloseButtonClick);

    add(background);
    add(closeButton);
}

void PipBoyState::onCloseButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

void PipBoyState::onKeyboardUp(std::shared_ptr<KeyboardEvent> event)
{
    if (event->keyCode() == SDLK_ESCAPE)
    {
        Game::getInstance()->popState();
    }
}

}