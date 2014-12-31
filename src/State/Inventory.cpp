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
#include <sstream>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "State.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/CritterObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Object.h"
#include "../Game/ObjectFactory.h"
#include "../Game/WeaponItemObject.h"
#include "../State/GameMenu.h"
#include "../State/InventoryDragItem.h"
#include "../State/Inventory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ItemsList.h"
#include "../UI/InventoryItem.h"
#include "../UI/TextArea.h"
#include "../UI/ImageList.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

Inventory::Inventory() : State()
{
    Game::getInstance()->mouse()->pushState(Mouse::ACTION);
}

Inventory::~Inventory()
{
    // If hand cursor now
    if (Game::getInstance()->mouse()->state() != Mouse::ACTION)
    {
        Game::getInstance()->mouse()->popState();
    }
    Game::getInstance()->mouse()->popState();
}

void Inventory::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto game = Game::getInstance();

    setX((game->renderer()->width()  - 499)/2);
    setY((game->renderer()->height() - 427)/2);

    addUI("background", new Image("art/intrface/invbox.frm"));
    getActiveUI("background")->addEventHandler("mouserightclick", [this](Event* event){ this->backgroundRightClick(dynamic_cast<MouseEvent*>(event)); });

    addUI("button_up",   new ImageButton(ImageButton::TYPE_INVENTORY_UP_ARROW,   128, 40));
    addUI("button_down", new ImageButton(ImageButton::TYPE_INVENTORY_DOWN_ARROW, 128, 65));

    addUI("button_done", new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, 438, 328));
    getActiveUI("button_done")->addEventHandler("mouseleftclick", [this](Event* event){ this->onDoneButtonClick(dynamic_cast<MouseEvent*>(event)); });

    // screen
    auto screenX = 300;
    auto screenY = 47;

    auto player = Game::getInstance()->player();

    addUI("player_name", new TextArea(player->name(), screenX, screenY));

    auto line1 = new Image(142, 1);
    line1->setX(screenX);
    line1->setY(screenY+16);
    line1->texture()->fill(0x3ff800ff); // default green color

    auto msg = ResourceManager::msgFileType("text/english/game/inventry.msg");

    std::string statsLabels;
    for (unsigned int i = 0; i != 7; ++i) statsLabels += msg->message(i)->text() + "\n";
    addUI("label_stats", new TextArea(statsLabels, screenX, screenY + 10*2));

    std::string statsValues;
    for (unsigned int i = 0; i != 7; ++i) statsValues += std::to_string(player->stat(i)) + "\n";
    addUI("label_stats_values", new TextArea(statsValues, screenX + 22, screenY + 20));

    std::stringstream ss;
    for (unsigned int i=7; i<14; i++)
    {
        ss << msg->message(i)->text() << "\n";
    }
    auto textLabel = new TextArea(ss.str(), screenX+40, screenY+20);

    // label: hit points
    ss.str("");
    ss << player->hitPoints();
    ss << "/";
    ss << player->hitPointsMax();
    auto hitPointsLabel = new TextArea(ss.str(), screenX+94, screenY+20);
    hitPointsLabel->setWidth(46)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    // label: armor class
    ss.str("");
    ss << player->armorClass();
    auto armorClassLabel = new TextArea(ss.str(), screenX+94, screenY+30);
    armorClassLabel->setWidth(46)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    // armorSlot, leftHand, rightHand
    Game::GameArmorItemObject* armorSlot = player->armorSlot();
    Game::GameItemObject* leftHand = player->leftHandSlot();
    Game::GameItemObject* rightHand = player->rightHandSlot();


    // label: damage treshold levels
    ss.str("");
    if (armorSlot)
    {
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_NORMAL) + armorSlot->damageThreshold(Game::GameArmorItemObject::DAMAGE_NORMAL) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_LASER) + armorSlot->damageThreshold(Game::GameArmorItemObject::DAMAGE_LASER) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_FIRE) + armorSlot->damageThreshold(Game::GameArmorItemObject::DAMAGE_FIRE) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_PLASMA) + armorSlot->damageThreshold(Game::GameArmorItemObject::DAMAGE_PLASMA) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_EXPLOSION) + armorSlot->damageThreshold(Game::GameArmorItemObject::DAMAGE_NORMAL) <<"/";
    }
    else
    {
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_NORMAL) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_LASER) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_FIRE) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_PLASMA) <<"/\n";
        ss << player->damageThreshold(Game::GameCritterObject::DAMAGE_EXPLOSION) <<"/";
    }
    auto damageThresholdLabel = new TextArea(ss.str(), screenX+94, screenY+40);
    damageThresholdLabel->setWidth(26)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    // label: damage resistance levels
    ss.str("");
    if (armorSlot)
    {
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_NORMAL) + armorSlot->damageResist(Game::GameArmorItemObject::DAMAGE_NORMAL) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_LASER) + armorSlot->damageResist(Game::GameArmorItemObject::DAMAGE_LASER) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_FIRE) + armorSlot->damageResist(Game::GameArmorItemObject::DAMAGE_FIRE) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_PLASMA) + armorSlot->damageResist(Game::GameArmorItemObject::DAMAGE_PLASMA) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_EXPLOSION) + armorSlot->damageResist(Game::GameArmorItemObject::DAMAGE_NORMAL) <<"%";
    }
    else
    {
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_NORMAL) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_LASER) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_FIRE) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_PLASMA) <<"%\n";
        ss << player->damageResist(Game::GameCritterObject::DAMAGE_EXPLOSION) <<"%";
    }
    auto damageResistanceLabel = new TextArea(ss.str(), screenX+120, screenY+40);

    auto line2 = new Image(142, 1);
    line2->setX(screenX);
    line2->setY(screenY+94);
    line2->texture()->fill(0x3ff800ff); // default green color

    auto line3 = new Image(142, 1);
    line3->setX(screenX);
    line3->setY(screenY+134);
    line3->texture()->fill(0x3ff800ff); // default green color

    // label: Total Wt: (20)
    auto weight = player->carryWeight();
    auto weightMax = player->carryWeightMax();

    ss.str("");
    ss << weight;
    auto totalWtLabel = new TextArea(msg->message(20), screenX+14, screenY+180);
    auto weightLabel = new TextArea(ss.str(), screenX+70, screenY+180);
    weightLabel->setWidth(24)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    ss.str("");
    ss << "/" << weightMax;
    auto weightMaxLabel = new TextArea(ss.str(), screenX+94, screenY+180);
    if (weight>weightMax)
    {
        weightLabel->setFont(ResourceManager::font("font1.aaf", 0xff0000ff));
    }

    // label: left hand
    ss.str("");
    if (leftHand)
    {
        ss << _handItemSummary(leftHand);
    }
    auto leftHandLabel = new TextArea(ss.str(), screenX, screenY+100);

    // label: right hand
    ss.str("");
    if (rightHand)
    {
        ss << _handItemSummary(rightHand);
    }
    auto rightHandLabel = new TextArea(ss.str(), screenX, screenY+140);

    // screen info
    auto screenLabel = new TextArea("", screenX, screenY+20);
    screenLabel->setWidth(140); //screen size
    screenLabel->setHeight(168);
    screenLabel->setVisible(false);
    screenLabel->setWordWrap(true);


    addUI(line1);
    addUI("textLabel", textLabel);
    addUI("hitPointsLabel", hitPointsLabel);
    addUI("armorClassLabel", armorClassLabel);
    addUI("damageThresholdLabel", damageThresholdLabel);
    addUI("damageResistanceLabel", damageResistanceLabel);
    addUI("line2", line2);
    addUI("line3", line3);
    addUI("totalWtLabel", totalWtLabel);
    addUI("weightLabel", weightLabel);
    addUI("weightMaxLabel", weightMaxLabel);
    addUI("leftHandLabel", leftHandLabel);
    addUI("rightHandLabel", rightHandLabel);
    addUI("screenLabel", screenLabel);

    auto inventoryList = new ItemsList(40, 40);
    inventoryList->setItems(game->player()->inventory());
    addUI(inventoryList);

    // BIG ICONS
    // icon: armor
    if (armorSlot)
    {
        auto inventoryItem = new InventoryItem(armorSlot, 154, 183);
        inventoryItem->setType(InventoryItem::TYPE_SLOT);
        inventoryItem->addEventHandler("itemdragstop", [inventoryList](Event* event){ inventoryList->onItemDragStop(dynamic_cast<MouseEvent*>(event)); });
        inventoryList->addEventHandler("itemdragstop", [inventoryItem](Event* event){ inventoryItem->onArmorDragStop(dynamic_cast<MouseEvent*>(event)); });
        addUI(inventoryItem);
    }

    // icon: left hand
    if (leftHand)
    {
        auto inventoryItem = new InventoryItem(leftHand, 154, 286);
        inventoryItem->setType(InventoryItem::TYPE_SLOT);
        inventoryItem->addEventHandler("itemdragstop", [inventoryList](Event* event){ inventoryList->onItemDragStop(dynamic_cast<MouseEvent*>(event)); });
        inventoryList->addEventHandler("itemdragstop", [inventoryItem](Event* event){ inventoryItem->onHandDragStop(dynamic_cast<MouseEvent*>(event)); });
        addUI(inventoryItem);
    }

    // icon: right hand
    if (rightHand)
    {
        auto inventoryItem = new InventoryItem(rightHand, 247, 286);
        inventoryItem->setType(InventoryItem::TYPE_SLOT);
        inventoryItem->addEventHandler("itemdragstop", [inventoryList](Event* event){ inventoryList->onItemDragStop(dynamic_cast<MouseEvent*>(event)); });
        inventoryList->addEventHandler("itemdragstop", [inventoryItem](Event* event){ inventoryItem->onHandDragStop(dynamic_cast<MouseEvent*>(event)); });
        addUI(inventoryItem);
    }

}

void Inventory::onDoneButtonClick(MouseEvent* event)
{
    Game::getInstance()->popState();
}

void Inventory::onArmorSlotMouseDown(MouseEvent* event)
{
    if (Game::getInstance()->mouse()->state() == Mouse::HAND)
    {
        auto itemUi = dynamic_cast<ImageList*>(event->emitter());
        Game::getInstance()->pushState(new InventoryDragItem(itemUi));
    }
    else
    {
        auto itemPID = Game::getInstance()->player()->armorSlot()->PID();
        _screenShow(itemPID);
    }
}

void Inventory::onLeftHandSlotMouseDown(MouseEvent* event)
{
    if (Game::getInstance()->mouse()->state() == Mouse::HAND)
    {
        auto itemUi = dynamic_cast<ImageList*>(event->emitter());
        Game::getInstance()->pushState(new InventoryDragItem(itemUi));
    }
    else
    {
        auto itemPID = Game::getInstance()->player()->leftHandSlot()->PID();
        _screenShow(itemPID);
    }
}

void Inventory::onRightHandSlotMouseDown(MouseEvent* event)
{
    if (Game::getInstance()->mouse()->state() == Mouse::HAND)
    {
        auto itemUi = dynamic_cast<ImageList*>(event->emitter());
        Game::getInstance()->pushState(new InventoryDragItem(itemUi));
    }
    else
    {
        auto itemPID = Game::getInstance()->player()->rightHandSlot()->PID();
        _screenShow(itemPID);
    }
}

//void Inventory::onSlotMouseDown(MouseEvent* event)
//{
//    auto state = dynamic_cast<Inventory*>(event->reciever());
//    auto itemUi = dynamic_cast<ImageList*>(event->emitter());
//    itemUi->setCurrentImage(1);
//    itemUi->setX(event->x() - itemUi->width()*0.5);
//    itemUi->setY(event->y() - itemUi->height()*0.5);
//}

//void Inventory::onSlotMouseUp(MouseEvent* event)
//{
//    auto itemUi = dynamic_cast<ImageList*>(event->emitter());
//    itemUi->setCurrentImage(0);
//    itemUi->setX(event->x() - itemUi->width()*0.5);
//    itemUi->setY(event->y() - itemUi->height()*0.5);
//}

//void Inventory::onSlotDrag(MouseEvent* event)
//{
//    //auto item = dynamic_cast<GameItemObject*>(event->reciever());
//    auto itemUi = dynamic_cast<ImageList*>(event->emitter());
//    //auto dragUi = item->inventoryDragUi();
//    itemUi->setX(itemUi->x() + event->xOffset());
//    itemUi->setY(itemUi->y() + event->yOffset());
//    //Game::getInstance()->states()->back()->ui()->push_back(dragUi);
//}

std::string Inventory::_handItemSummary (Game::GameItemObject* hand)
{
    std::stringstream ss;
    if (hand)
    {
        ss << hand->name() << "\n";
        // is it weapon
        if (hand->subtype() == Game::GameObject::TYPE_ITEM_WEAPON)
        {
            auto weapon = dynamic_cast<Game::GameWeaponItemObject*>(hand);
            ss << "Dmg: " << weapon->damageMin() << "-" << weapon->damageMax() << " ";
            ss << "Rng: " << weapon->rangePrimary();
            // has it ammo?
            if (weapon->ammoType() != 0)
            {
                ss << "\nAmmo: /" << weapon->ammoCapacity() << " ";
                auto ammo = Game::GameObjectFactory::createObject(weapon->ammoPID());
                ss << ammo->name();
            }
        }
    }
    else
    {
        ss << "No item\nUnarmed dmg:";
    }
    return ss.str();
}

void Inventory::backgroundRightClick(MouseEvent* event)
{
    auto mouse = Game::getInstance()->mouse();
    if (mouse->state() == Mouse::ACTION)
    {
        mouse->pushState(Mouse::HAND);
    }
    else
    {
        mouse->popState();
        //state->_screenShow(1);
    }
    _screenShow(0);
}

void Inventory::_screenShow (unsigned int PID)
{
    auto player = Game::getInstance()->player();
    auto playerNameLabel = getTextArea("player_name");
    auto statsLabel = getTextArea("label_stats");
    auto statsValuesLabel = getTextArea("label_stats_values");
    auto textLabel = getTextArea("textLabel");
    auto hitPointsLabel = getTextArea("hitPointsLabel");
    auto armorClassLabel = getTextArea("armorClassLabel");
    auto damageThresholdLabel = getTextArea("damageThresholdLabel");
    auto damageResistanceLabel = getTextArea("damageResistanceLabel");
    auto line2 = dynamic_cast<Image*>(getUI("line2"));
    auto line3 = dynamic_cast<Image*>(getUI("line3"));
    auto totalWtLabel = getTextArea("totalWtLabel");
    auto weightLabel = getTextArea("weightLabel");
    auto weightMaxLabel = getTextArea("weightMaxLabel");
    auto leftHandLabel = getTextArea("leftHandLabel");
    auto rightHandLabel = getTextArea("rightHandLabel");
    auto screenLabel = getTextArea("screenLabel");

    if (PID == 0)
    {
        playerNameLabel->setText(player->name());
    }
    else
    {
        auto msg = ResourceManager::msgFileType("text/english/game/pro_item.msg");
        playerNameLabel->setText(msg->message(PID*100)->text()); // item name
        screenLabel->setText(msg->message(PID*100+1)->text()); // item dedcription
    }

    screenLabel->setVisible(PID != 0);
    statsLabel->setVisible(PID == 0);
    statsValuesLabel->setVisible(PID == 0);
    textLabel->setVisible(PID == 0);
    hitPointsLabel->setVisible(PID == 0);
    armorClassLabel->setVisible(PID == 0);
    damageThresholdLabel->setVisible(PID == 0);
    damageResistanceLabel->setVisible(PID == 0);
    line2->setVisible(PID == 0);
    line3->setVisible(PID == 0);
    totalWtLabel->setVisible(PID == 0);
    weightLabel->setVisible(PID == 0);
    weightMaxLabel->setVisible(PID == 0);
    leftHandLabel->setVisible(PID == 0);
    rightHandLabel->setVisible(PID == 0);
}


}
}
