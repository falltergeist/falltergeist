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
#include "../States/CritterBarterState.h"
#include "../States/CritterDialogState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{

CritterBarterState::CritterBarterState() : State()
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

    setX((Game::getInstance()->renderer()->width() - 640)*0.5);
    setY((Game::getInstance()->renderer()->height() - 480)*0.5 + 291);


    auto background = std::shared_ptr<Image>(new Image("art/intrface/barter.frm"));
    background->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterBarterState::onBackgroundClick);
    addUI(background);

    // Interface buttons
    auto offerButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, 40, 162));
    addUI(offerButton);

    auto talkButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, 583, 162));
    talkButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterBarterState::onTalkButtonClick);
    addUI(talkButton);

    auto mineInventoryScrollUpButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_UP_ARROW, 190, 56));
    addUI(mineInventoryScrollUpButton);
    auto mineInventoryScrollDownButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_DOWN_ARROW, 190, 82));
    addUI(mineInventoryScrollDownButton);

    auto theirsInventoryScrollUpButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_UP_ARROW, 421, 56));
    addUI(theirsInventoryScrollUpButton);
    auto theirsInventoryScrollDownButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_DOWN_ARROW, 421, 82));
    addUI(theirsInventoryScrollDownButton);
}

void CritterBarterState::onTalkButtonClick(std::shared_ptr<Event> event)
{
    Game::getInstance()->popState();
}

void CritterBarterState::onBackgroundClick(std::shared_ptr<Event> event)
{
    // to prevent event propagation to dialog state
    event->setHandled(true);
}

}
