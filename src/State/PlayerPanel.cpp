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
#include "../Audio/AudioMixer.h"
#include "../Game.h"
#include "../Graphics/ActiveUI.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Input/Mouse.h"
#include "../Game/GameDudeObject.h"
#include "../State/GameMenu.h"
#include "../State/Inventory.h"
#include "../State/PipBoy.h"
#include "../State/PlayerEdit.h"
#include "../State/PlayerPanel.h"
#include "../State/Skilldex.h"
#include "../State/WorldMap.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/SmallCounter.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

PlayerPanel::PlayerPanel() : State()
{
}

PlayerPanel::~PlayerPanel()
{
}

void PlayerPanel::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(false);

    auto game = Game::getInstance();

    setX((game->renderer()->width() - 640)*0.5);
    setY(game->renderer()->height() - 99);

    addUI("background", new Image("art/intrface/iface.frm"));
    getActiveUI("background")->addEventHandler("mouseleftdown", [this](Event* event){ this->onPanelMouseDown(dynamic_cast<MouseEvent*>(event)); });
    getActiveUI("background")->addEventHandler("mousein", [this](Event* event){ this->onPanelMouseIn(dynamic_cast<MouseEvent*>(event)); });
    getActiveUI("background")->addEventHandler("mouseout", [this](Event* event){ this->onPanelMouseOut(dynamic_cast<MouseEvent*>(event)); });

    addUI("change_hand_button", new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, 218, 5));
    getActiveUI("change_hand_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onChangeHandButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("inventory_button", new ImageButton(ImageButton::TYPE_PANEL_INVENTORY, 211, 40));
    getActiveUI("inventory_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onInventoryButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("options_button", new ImageButton(ImageButton::TYPE_PANEL_OPTIONS, 210, 61));
    getActiveUI("options_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onOptionsButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("attack_button", new ImageButton(ImageButton::TYPE_PANEL_ATTACK, 267, 25));

    addUI("hit_points", new SmallCounter(471, 40));
    getSmallCounter("hit_points")->setNumber(game->player()->hitPoints());
    getSmallCounter("hit_points")->setType(SmallCounter::SIGNED);

    addUI("armor_class", new SmallCounter(472, 76));
    getSmallCounter("armor_class")->setNumber(game->player()->armorClass());
    getSmallCounter("armor_class")->setType(SmallCounter::SIGNED);

    addUI("skilldex_button", new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, 523, 5));
    getActiveUI("skilldex_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onSkilldexButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("map_button", new ImageButton(ImageButton::TYPE_PANEL_MAP, 526, 39));
    getActiveUI("map_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onMapButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("cha_button", new ImageButton(ImageButton::TYPE_PANEL_CHA, 526, 58));
    getActiveUI("cha_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onChaButtonClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("pip_button", new ImageButton(ImageButton::TYPE_PANEL_PIP, 526, 77));
    getActiveUI("pip_button")->addEventHandler("mouseleftclick", [this](Event* event){ this->onPipBoyButtonClick(dynamic_cast<MouseEvent*>(event)); });
}

void PlayerPanel::render()
{
    State::render();

    // object in hand
    if (auto item = Game::getInstance()->player()->currentHandSlot())
    {
        auto itemUi = item->inventoryDragUi();
        itemUi->setX(x() + 360 - itemUi->width()*0.5);
        itemUi->setY(y() + 60 - itemUi->height()*0.5);
        itemUi->render();
    }
}

void PlayerPanel::think()
{
    State::think();
    // object in hand
    if (auto item = Game::getInstance()->player()->currentHandSlot())
    {
        auto itemUi = item->inventoryDragUi();
        itemUi->think();
    }
}

void PlayerPanel::handle(Event* event)
{
    // object in hand
    if (auto item = Game::getInstance()->player()->currentHandSlot())
    {
        auto itemUi = item->inventoryDragUi();
        itemUi->handle(event);
        if (event->handled()) return;
    }
    State::handle(event);
}

void PlayerPanel::onPanelMouseDown(MouseEvent* event)
{
    event->setHandled(true);
}

void PlayerPanel::onInventoryButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new Inventory());
}

void PlayerPanel::onOptionsButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new GameMenu());
}

void PlayerPanel::onSkilldexButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new Skilldex());
}

void PlayerPanel::onMapButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new WorldMap());
}

void PlayerPanel::onChaButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new PlayerEdit());
}

void PlayerPanel::onPipBoyButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new PipBoy());
}

void PlayerPanel::onChangeHandButtonClick(MouseEvent* event)
{
    auto player = Game::getInstance()->player();
    player->setCurrentHand(player->currentHand() == GameCritterObject::HAND_LEFT ? GameCritterObject::HAND_RIGHT : GameCritterObject::HAND_LEFT);
}

void PlayerPanel::onPanelMouseIn(MouseEvent* event)
{
    Game::getInstance()->mouse()->pushState(Mouse::BIG_ARROW);
}

void PlayerPanel::onPanelMouseOut(MouseEvent* event)
{
    auto mouse = Game::getInstance()->mouse();
    if (mouse->scrollState())
    {
        // this trick is needed for correct cursor type returning on scrolling
        auto state = mouse->state();
        mouse->popState();
        mouse->popState();
        mouse->pushState(state);
    }
    else
    {
        mouse->popState();
    }
}

void PlayerPanel::onPanelMouseUp(MouseEvent* event)
{
}

}
}
