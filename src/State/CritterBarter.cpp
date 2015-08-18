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
#include "../State/CritterBarter.h"
#include "../State/CritterDialog.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

CritterBarter::CritterBarter() : State()
{
}

CritterBarter::~CritterBarter()
{
}

void CritterBarter::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(true);

    setX((Game::getInstance()->renderer()->width() - 640)*0.5);
    setY((Game::getInstance()->renderer()->height() - 480)*0.5 + 291);

    addUI("background",new UI::Image("art/intrface/barter.frm"));
    getUI("background")->addEventHandler("mouseleftclick", std::bind(&CritterBarter::onBackgroundClick, this, std::placeholders::_1));

    addUI("offerButton", new UI::ImageButton(UI::ImageButton::Type::DIALOG_RED_BUTTON, 40, 162));

    addUI("talkButton", new UI::ImageButton(UI::ImageButton::Type::DIALOG_RED_BUTTON, 583, 162));
    getUI("talkButton")->addEventHandler("mouseleftclick", std::bind(&CritterBarter::onTalkButtonClick, this, std::placeholders::_1));

    addUI("mineInventoryScrollUpButton",   new UI::ImageButton(UI::ImageButton::Type::DIALOG_UP_ARROW,   190, 56));
    addUI("mineInventoryScrollDownButton", new UI::ImageButton(UI::ImageButton::Type::DIALOG_DOWN_ARROW, 190, 82));

    addUI("theirsInventoryScrollUpButton",   new UI::ImageButton(UI::ImageButton::Type::DIALOG_UP_ARROW,   421, 56));
    addUI("theirsInventoryScrollDownButton", new UI::ImageButton(UI::ImageButton::Type::DIALOG_DOWN_ARROW, 421, 82));
}

void CritterBarter::onTalkButtonClick(Event::Event* event)
{
    Game::getInstance()->popState();
}

void CritterBarter::onBackgroundClick(Event::Event* event)
{
    // to prevent event propagation to dialog state
    event->setHandled(true);
}

}
}
