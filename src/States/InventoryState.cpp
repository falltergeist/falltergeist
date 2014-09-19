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
#include <sstream>
#include <iostream>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Location.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/State.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../States/GameMenuState.h"
#include "../States/InventoryState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/ImageList.h"

// Third party includes

namespace Falltergeist
{

InventoryState::InventoryState() : State()
{
}

InventoryState::~InventoryState()
{
}

void InventoryState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto player = Game::getInstance()->player();

    std::shared_ptr<GameArmorItemObject> armorSlot = player->armorSlot();
    std::shared_ptr<GameItemObject> leftHand = player->leftHandSlot();
    std::shared_ptr<GameItemObject> rightHand = player->rightHandSlot();

    // background
    auto background = std::shared_ptr<Image>(new Image("art/intrface/invbox.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5-50;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // buttons
    auto upButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_INVENTORY_UP_ARROW, backgroundX+128, backgroundY+40));
    auto downButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_INVENTORY_DOWN_ARROW, backgroundX+128, backgroundY+65));
    auto doneButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+438, backgroundY+328));

    // events
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &InventoryState::onDoneButtonClick);

    // screen
    auto screenX = backgroundX + background->width() - 202;
    auto screenY = backgroundY + background->height() - 332; //330
    auto font = ResourceManager::font("font1.aaf");

    // name
    auto playerNameLabel = std::shared_ptr<TextArea>(new TextArea(player->name(), screenX, screenY));

    auto line1 = std::shared_ptr<Image>(new Image(142, 1));
    line1->setX(screenX);
    line1->setY(screenY+16);
    line1->texture()->fill(0x3ff800ff); // default green color

    auto msg = ResourceManager::msgFileType("text/english/game/inventry.msg");
    // label: ST (0)
    auto stLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(0), screenX, screenY+20));
    // label: PE (1)
    auto peLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(1), screenX, screenY+20+10));
    // label: EN (2)
    auto enLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(2), screenX, screenY+20+10*2));
    // label: CH (3)
    auto chLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(3), screenX, screenY+20+10*3));
    // label: IN (4)
    auto inLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(4), screenX, screenY+20+10*4));
    // label: AG (5)
    auto agLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(5), screenX, screenY+20+10*5));
    // label: LK (6)
    auto lkLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(6), screenX, screenY+20+10*6));

    std::stringstream ss;
    for (unsigned int i=0; i<7; i++)
    {
        ss << player->stat(i) << "\n";
    }
    auto statsLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+22, screenY+20));

    ss.str("");
    for (unsigned int i=7; i<14; i++)
    {
        ss << msg->message(i)->text() << "\n";
    }
    auto textLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+40, screenY+20));

    // label: hit points
    ss.str("");
    ss << player->hitPoints();
    ss << "/";
    ss << player->hitPointsMax();
    auto hitPointsLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+20));
    hitPointsLabel->setFont(font)->setWidth(46)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    // label: armor class
    ss.str("");
    ss << player->armorClass();
    auto armorClassLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+30));
    armorClassLabel->setFont(font)->setWidth(46)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    // label: damage treshold levels
    ss.str("");
    ss << player->damageThreshold(GameCritterObject::DAMAGE_NORMAL) + armorSlot->damageThreshold(GameArmorItemObject::DAMAGE_NORMAL) <<"/\n";
    ss << player->damageThreshold(GameCritterObject::DAMAGE_LASER) + armorSlot->damageThreshold(GameArmorItemObject::DAMAGE_LASER) <<"/\n";
    ss << player->damageThreshold(GameCritterObject::DAMAGE_FIRE) + armorSlot->damageThreshold(GameArmorItemObject::DAMAGE_FIRE) <<"/\n";
    ss << player->damageThreshold(GameCritterObject::DAMAGE_PLASMA) + armorSlot->damageThreshold(GameArmorItemObject::DAMAGE_PLASMA) <<"/\n";
    ss << player->damageThreshold(GameCritterObject::DAMAGE_EXPLOSION) + armorSlot->damageThreshold(GameArmorItemObject::DAMAGE_NORMAL) <<"/";
    auto damageThresholdLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+40));
    damageThresholdLabel->setFont(font)->setWidth(26)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    // label: damage resistance levels
    ss.str("");
    ss << player->damageResist(GameCritterObject::DAMAGE_NORMAL) + armorSlot->damageResist(GameArmorItemObject::DAMAGE_NORMAL) <<"%\n";
    ss << player->damageResist(GameCritterObject::DAMAGE_LASER) + armorSlot->damageResist(GameArmorItemObject::DAMAGE_LASER) <<"%\n";
    ss << player->damageResist(GameCritterObject::DAMAGE_FIRE) + armorSlot->damageResist(GameArmorItemObject::DAMAGE_FIRE) <<"%\n";
    ss << player->damageResist(GameCritterObject::DAMAGE_PLASMA) + armorSlot->damageResist(GameArmorItemObject::DAMAGE_PLASMA) <<"%\n";
    ss << player->damageResist(GameCritterObject::DAMAGE_EXPLOSION) + armorSlot->damageResist(GameArmorItemObject::DAMAGE_NORMAL) <<"%";
    auto damageResistanceLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+120, screenY+40));

    auto line2 = std::shared_ptr<Image>(new Image(142, 1));
    line2->setX(screenX);
    line2->setY(screenY+94);
    line2->texture()->fill(0x3ff800ff); // default green color

    auto line3 = std::shared_ptr<Image>(new Image(142, 1));
    line3->setX(screenX);
    line3->setY(screenY+134);
    line3->texture()->fill(0x3ff800ff); // default green color

    // label: Total Wt: (20)
    auto weight = player->carryWeight();
    auto weightMax = player->carryWeightMax();

    ss.str("");
    ss << weight;
    auto totalWtLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(20), screenX+14, screenY+180));
    auto weightLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+70, screenY+180));
    weightLabel->setFont(font)->setWidth(24)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    ss.str("");
    ss << "/" << weightMax;
    auto weightMaxLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+180));
    if (weight>weightMax)
    {
        weightLabel->setFont(ResourceManager::font("font1.aaf", 0xff0000ff));
    }

    // label: left hand
    ss.str("");
    if (leftHand)
    {
        ss << leftHand->name() << "\n";
        // is it weapon
        if (leftHand->subtype() == GameObject::TYPE_ITEM_WEAPON)
        {
            auto weapon = std::dynamic_pointer_cast<GameWeaponItemObject>(leftHand);
            ss << "Dmg: " << weapon->damageMin() << "-" << weapon->damageMax() << "  ";
            ss << "Rng: " << weapon->rangePrimary();
            // has it ammo?
            if (weapon->ammoType() != 0)
            {
                ss << "\nAmmo: /" << weapon->ammoCapacity() << " ";
                auto ammo = Location::createObject(weapon->ammoPID());
                ss << ammo->name();
            }
        }
    }
    else
    {
        ss << "No item\nUnarmed dmg:";
    }
    auto leftHandLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX, screenY+100));

    // label: right hand
    ss.str("");
    if (rightHand)
    {
        ss << rightHand->name() << "\n";
        // is it weapon
        if (rightHand->subtype() == GameObject::TYPE_ITEM_WEAPON)
        {
            auto weapon = std::dynamic_pointer_cast<GameWeaponItemObject>(rightHand);
            ss << "Dmg: " << weapon->damageMin() << "-" << weapon->damageMax() << "  ";
            ss << "Rng: " << weapon->rangePrimary();
            // has it ammo?
            if (weapon->ammoType() != 0)
            {
                ss << "\nAmmo: /" << weapon->ammoCapacity() << " ";
                auto ammo = Location::createObject(weapon->ammoPID());
                ss << ammo->name();
            }
        }
    }
    else
    {
        ss << "No item\nUnarmed dmg:";
    }
    auto rightHandLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX, screenY+140));

    add(background);
    add(playerNameLabel);
    add(line1);
    add(stLabel);
    add(peLabel);
    add(enLabel);
    add(chLabel);
    add(inLabel);
    add(agLabel);
    add(lkLabel);
    add(statsLabel);
    add(textLabel);
    add(hitPointsLabel);
    add(armorClassLabel);
    add(damageThresholdLabel);
    add(damageResistanceLabel);
    add(line2);
    add(line3);
    add(totalWtLabel);
    add(weightLabel);
    add(weightMaxLabel);
    add(leftHandLabel);
    add(rightHandLabel);
    add(upButton);
    add(downButton);
    add(doneButton);

    // BIG ICONS
    // icon: armor
    std::shared_ptr<ImageList> armorUi = std::shared_ptr<ImageList>(new ImageList());
    armorUi->addImage(std::shared_ptr<Image>(new Image(armorSlot->inventorySlotUi()->texture())));
    armorUi->addImage(std::shared_ptr<Image>(new Image(armorSlot->inventoryDragUi()->texture())));
    armorUi->setX(backgroundX + 200 - armorUi->width()*0.5);
    armorUi->setY(backgroundY + 215 - armorUi->height()*0.5);
    add(armorUi);

    armorUi->addEventHandler("mousedrag", armorSlot.get(), (EventRecieverMethod) &InventoryState::onSlotDrag);
    armorUi->addEventHandler("mouseleftdown", armorSlot.get(), (EventRecieverMethod) &InventoryState::onSlotMouseDown);
    armorUi->addEventHandler("mouseleftup", armorSlot.get(), (EventRecieverMethod) &InventoryState::onSlotMouseUp);

    // icon: left hand
    std::shared_ptr<ImageList> leftHandUi = std::shared_ptr<ImageList>(new ImageList());
    leftHandUi->addImage(std::shared_ptr<Image>(new Image(leftHand->inventorySlotUi()->texture())));
    leftHandUi->addImage(std::shared_ptr<Image>(new Image(leftHand->inventoryDragUi()->texture())));
    leftHandUi->setX(backgroundX + 200 - leftHandUi->width()*0.5);
    leftHandUi->setY(backgroundY + 317 - leftHandUi->height()*0.5);
    add(leftHandUi);

    leftHandUi->addEventHandler("mousedrag", leftHand.get(), (EventRecieverMethod) &InventoryState::onSlotDrag);
    leftHandUi->addEventHandler("mouseleftdown", leftHand.get(), (EventRecieverMethod) &InventoryState::onSlotMouseDown);
    leftHandUi->addEventHandler("mouseleftup", leftHand.get(), (EventRecieverMethod) &InventoryState::onSlotMouseUp);

    // icon: right hand
    std::shared_ptr<ImageList> rightHandUi = std::shared_ptr<ImageList>(new ImageList());
    rightHandUi->addImage(std::shared_ptr<Image>(new Image(rightHand->inventorySlotUi()->texture())));
    rightHandUi->addImage(std::shared_ptr<Image>(new Image(rightHand->inventoryDragUi()->texture())));
    rightHandUi->setX(backgroundX + 290 - rightHandUi->width()*0.5);
    rightHandUi->setY(backgroundY + 317 - rightHandUi->height()*0.5);
    add(rightHandUi);

    rightHandUi->addEventHandler("mousedrag", rightHand.get(), (EventRecieverMethod) &InventoryState::onSlotDrag);
    rightHandUi->addEventHandler("mouseleftdown", rightHand.get(), (EventRecieverMethod) &InventoryState::onSlotMouseDown);
    rightHandUi->addEventHandler("mouseleftup", rightHand.get(), (EventRecieverMethod) &InventoryState::onSlotMouseUp);

}

void InventoryState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();

}

void InventoryState::onSlotMouseDown(std::shared_ptr<MouseEvent> event)
{
    auto itemUi = dynamic_cast<ImageList*>(event->emitter());
    itemUi->setCurrentImage(1);
    itemUi->setX(event->x() - itemUi->width()*0.5);
    itemUi->setY(event->y() - itemUi->height()*0.5);
}

void InventoryState::onSlotMouseUp(std::shared_ptr<MouseEvent> event)
{
    auto itemUi = dynamic_cast<ImageList*>(event->emitter());
    itemUi->setCurrentImage(0);
    itemUi->setX(event->x() - itemUi->width()*0.5);
    itemUi->setY(event->y() - itemUi->height()*0.5);
}

void InventoryState::onSlotDrag(std::shared_ptr<MouseEvent> event)
{
    //auto item = dynamic_cast<GameItemObject*>(event->reciever());
    auto itemUi = dynamic_cast<ImageList*>(event->emitter());
    //auto dragUi = item->inventoryDragUi();
    itemUi->setX(itemUi->x() + event->xOffset());
    itemUi->setY(itemUi->y() + event->yOffset());
    //Game::getInstance()->states()->back()->ui()->push_back(dragUi);
}

}
