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
#include "../Game.h"
#include "../Graphics/Renderer.h"
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

    setFullscreen(false);
    setModal(true);

    auto background = new Image("art/intrface/review.frm");
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Interface buttons
    auto doneButton = new ImageButton(ImageButton::TYPE_DIALOG_DONE_BUTTON, backgroundX + 500, backgroundY + 398);
    doneButton->addEventHandler("mouseleftclick", std::bind(&CritterDialogReviewState::onDoneButtonClick, this, std::placeholders::_1));

    auto upButton = new ImageButton(ImageButton::TYPE_DIALOG_BIG_UP_ARROW, backgroundX + 476, backgroundY + 154);

    auto downButton = new ImageButton(ImageButton::TYPE_DIALOG_BIG_DOWN_ARROW, backgroundX + 476, backgroundY + 192);

    addUI(background);
    addUI(doneButton);
    addUI(upButton);
    addUI(downButton);
}

void CritterDialogReviewState::onDoneButtonClick(Event* event)
{
    Game::getInstance()->popState();
}

}
