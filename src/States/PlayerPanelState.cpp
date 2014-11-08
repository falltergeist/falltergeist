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
#include "../Engine/Audio/AudioMixer.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/ActiveUI.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Input/Mouse.h"
#include "../Game/GameDudeObject.h"
#include "../States/GameMenuState.h"
#include "../States/InventoryState.h"
#include "../States/PipBoyState.h"
#include "../States/PlayerEditState.h"
#include "../States/PlayerPanelState.h"
#include "../States/SkilldexState.h"
#include "../States/WorldMapState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/SmallCounter.h"

// Third party includes

namespace Falltergeist
{

PlayerPanelState::PlayerPanelState() : State()
{
}

PlayerPanelState::~PlayerPanelState()
{
}

void PlayerPanelState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(false);

    auto game = Game::getInstance();

    setX((game->renderer()->width() - 640)*0.5);
    setY(game->renderer()->height() - 99);

    addUI("background", new Image("art/intrface/iface.frm"));
    getActiveUI("background")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onPanelMouseDown);
    getActiveUI("background")->addEventHandler("mousein", this, (EventRecieverMethod) &PlayerPanelState::onPanelMouseIn);
    getActiveUI("background")->addEventHandler("mouseout", this, (EventRecieverMethod) &PlayerPanelState::onPanelMouseOut);

    addUI("change_hand_button", new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, 218, 5));
    getActiveUI("change_hand_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onChangeHandButtonClick);
    getActiveUI("change_hand_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("change_hand_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);

    addUI("inventory_button", new ImageButton(ImageButton::TYPE_PANEL_INVENTORY, 211, 40));
    getActiveUI("inventory_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onInventoryButtonClick);
    getActiveUI("inventory_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("inventory_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);

    addUI("options_button", new ImageButton(ImageButton::TYPE_PANEL_OPTIONS, 210, 61));
    getActiveUI("options_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onOptionsButtonClick);
    getActiveUI("options_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("options_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);

    addUI("attack_button", new ImageButton(ImageButton::TYPE_PANEL_ATTACK, 267, 25));
    getActiveUI("attack_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDownAttack);
    getActiveUI("attack_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUpAttack);

    addUI("hit_points", new SmallCounter(471, 40));
    getSmallCounter("hit_points")->setNumber(game->player()->hitPoints());
    getSmallCounter("hit_points")->setType(SmallCounter::SIGNED);

    addUI("armor_class", new SmallCounter(472, 76));
    getSmallCounter("armor_class")->setNumber(game->player()->armorClass());
    getSmallCounter("armor_class")->setType(SmallCounter::SIGNED);

    addUI("skilldex_button", new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, 523, 5));
    getActiveUI("skilldex_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onSkilldexButtonClick);
    getActiveUI("skilldex_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("skilldex_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);

    addUI("map_button", new ImageButton(ImageButton::TYPE_PANEL_MAP, 526, 39));
    getActiveUI("map_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onMapButtonClick);
    getActiveUI("map_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("map_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);

    addUI("cha_button", new ImageButton(ImageButton::TYPE_PANEL_CHA, 526, 58));
    getActiveUI("cha_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onChaButtonClick);
    getActiveUI("cha_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("cha_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);

    addUI("pip_button", new ImageButton(ImageButton::TYPE_PANEL_PIP, 526, 77));
    getActiveUI("pip_button")->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PlayerPanelState::onPipBoyButtonClick);
    getActiveUI("pip_button")->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &PlayerPanelState::onMouseDown);
    getActiveUI("pip_button")->addEventHandler("mouseleftup", this, (EventRecieverMethod) &PlayerPanelState::onMouseUp);
}

void PlayerPanelState::render()
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

void PlayerPanelState::think()
{
    State::think();
    // object in hand
    if (auto item = Game::getInstance()->player()->currentHandSlot())
    {
        auto itemUi = item->inventoryDragUi();
        itemUi->think();
    }
}

void PlayerPanelState::handle(Event* event)
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

void PlayerPanelState::onPanelMouseDown(MouseEvent* event)
{
    event->setHandled(true);
}

void PlayerPanelState::onInventoryButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new InventoryState());
}

void PlayerPanelState::onOptionsButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new GameMenuState());
}

void PlayerPanelState::onSkilldexButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new SkilldexState());
}

void PlayerPanelState::onMapButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new WorldMapState());
}

void PlayerPanelState::onChaButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new PlayerEditState());
}

void PlayerPanelState::onPipBoyButtonClick(MouseEvent* event)
{
    Game::getInstance()->pushState(new PipBoyState());
}

void PlayerPanelState::onChangeHandButtonClick(MouseEvent* event)
{
    auto player = Game::getInstance()->player();
    player->setCurrentHand(player->currentHand() == GameCritterObject::HAND_LEFT ? GameCritterObject::HAND_RIGHT : GameCritterObject::HAND_LEFT);
}

void PlayerPanelState::onPanelMouseIn(MouseEvent* event)
{
    Game::getInstance()->mouse()->pushState(Mouse::BIG_ARROW);
}

void PlayerPanelState::onPanelMouseOut(MouseEvent* event)
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

void PlayerPanelState::onPanelMouseUp(MouseEvent* event)
{
}

void PlayerPanelState::onMouseDown(MouseEvent* event)
{
    Game::getInstance()->mixer()->playACMSound(ResourceManager::acmFileType("sound/sfx/butin2.acm"));
}

void PlayerPanelState::onMouseUp(MouseEvent* event)
{
    Game::getInstance()->mixer()->playACMSound(ResourceManager::acmFileType("sound/sfx/butin1.acm"));
}

void PlayerPanelState::onMouseDownAttack(MouseEvent* event)
{
    Game::getInstance()->mixer()->playACMSound(ResourceManager::acmFileType("sound/sfx/butin3.acm"));
}

void PlayerPanelState::onMouseUpAttack(MouseEvent* event)
{
    Game::getInstance()->mixer()->playACMSound(ResourceManager::acmFileType("sound/sfx/butout3.acm"));
}

}
