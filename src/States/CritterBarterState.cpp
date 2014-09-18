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
#include "../States/CritterBarterState.h"
#include "../States/CritterDialogState.h"
#include "../States/CritterTalkState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{

CritterBarterState::CritterBarterState(int offsetX, int offsetY) : State(), _offsetX(offsetX), _offsetY(offsetY)
{
}

CritterBarterState::CritterBarterState() : CritterBarterState(0, 0)
{
}

CritterBarterState::~CritterBarterState()
{
}

void CritterBarterState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(true);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/barter.frm"));
    background->setX(_offsetX);
    background->setY(_offsetY);

    // Interface buttons
    auto offerButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, _offsetX+40, _offsetY+162));
    auto talkButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, _offsetX+583, _offsetY+162));
    talkButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterBarterState::onTalkButtonClick);

    auto mineInventoryScrollUpButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_UP_ARROW, _offsetX + 190, _offsetY + 56));
    auto mineInventoryScrollDownButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_DOWN_ARROW, _offsetX + 190, _offsetY + 82));

    auto theirsInventoryScrollUpButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_UP_ARROW, _offsetX + 421, _offsetY + 56));
    auto theirsInventoryScrollDownButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_DOWN_ARROW, _offsetX + 421, _offsetY + 82));

    add(background);
    add(offerButton);
    add(talkButton);
    add(mineInventoryScrollUpButton);
    add(mineInventoryScrollDownButton);
    add(theirsInventoryScrollUpButton);
    add(theirsInventoryScrollDownButton);
}

int CritterBarterState::offsetX()
{
    return _offsetX;
}

void CritterBarterState::setOffsetX(int offsetX)
{
    _offsetX = offsetX;
}

int CritterBarterState::offsetY()
{
    return _offsetY;
}

void CritterBarterState::setOffsetY(int offsetY)
{
    _offsetY = offsetY;
}

void CritterBarterState::onTalkButtonClick(std::shared_ptr<Event> event)
{
    auto critterTalkState = Game::getInstance()->dialog()->talk();
    Game::getInstance()->popState();
    Game::getInstance()->pushState(critterTalkState);
}

}