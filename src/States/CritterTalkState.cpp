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
#include <iostream>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../States/CritterTalkState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{

CritterTalkState::CritterTalkState() : CritterTalkState(0, 0)
{
}

CritterTalkState::CritterTalkState(int offsetX, int offsetY) : State(), _offsetX(offsetX), _offsetY(offsetY)
{
}

CritterTalkState::~CritterTalkState()
{
}

void CritterTalkState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(false);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/di_talk.frm"));
    auto backgroundOffsetX = _offsetX;
    auto backgroundOffsetY = _offsetY + 291;
    background->setX(backgroundOffsetX);
    background->setY(backgroundOffsetY);

    // Interface buttons
    auto reviewButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_REVIEW_BUTTON, _offsetX+13, _offsetY+445));
    auto barterButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, _offsetX+593, _offsetY+331));

    add(background);
    add(reviewButton);
    add(barterButton);
}

}
