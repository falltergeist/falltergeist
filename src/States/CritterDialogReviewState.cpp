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
#include "../States/CritterDialogReviewState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{


CritterDialogReviewState::CritterDialogReviewState() : State()
{
}

CritterDialogReviewState::~CritterDialogReviewState()
{
}

void CritterDialogReviewState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(true);
    setModal(true);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/review.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Interface buttons
    auto doneButton = std::shared_ptr<ImageButton>(
            new ImageButton(ImageButton::TYPE_DIALOG_DONE_BUTTON, backgroundX + 500, backgroundY + 398));
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterDialogReviewState::onDoneButtonClick);

    auto upButton = std::shared_ptr<ImageButton>(
            new ImageButton(ImageButton::TYPE_DIALOG_BIG_UP_BUTTON, backgroundX + 476, backgroundY + 154));

    auto downButton = std::shared_ptr<ImageButton>(
            new ImageButton(ImageButton::TYPE_DIALOG_BIG_DOWN_BUTTON, backgroundX + 476, backgroundY + 192));

    add(background);
    add(doneButton);
    add(upButton);
    add(downButton);
}

void CritterDialogReviewState::onDoneButtonClick(std::shared_ptr<Event> event)
{
    Game::getInstance()->popState();
}

}