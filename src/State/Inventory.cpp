/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Related headers
#include "../State/Inventory.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../functions.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/CritterObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/Object.h"
#include "../Game/ObjectFactory.h"
#include "../Game/WeaponItemObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Size.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/State.h"
#include "../State/GameMenu.h"
#include "../State/InventoryDragItem.h"
#include "../State/Location.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/InventoryItem.h"
#include "../UI/ItemsList.h"
#include "../UI/PlayerPanel.h"
#include "../UI/Rectangle.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        Inventory::Inventory() : State()
        {
            pushHandler().add([this](Event::State* ev)
                {
                    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::ACTION);
                });
            popHandler().add([this](Event::State* ev)
                {
                    // If hand cursor now
                    if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HAND)
                    {
                        Game::getInstance()->mouse()->popState();
                    }
                    Game::getInstance()->mouse()->popState();
                });
        }

        Inventory::~Inventory()
        {

        }

        void Inventory::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);

            auto game = Game::getInstance();
            auto panelHeight = Game::getInstance()->locationState()->playerPanel()->size().height();

            setPosition((game->renderer()->size() - Point(499, 377 + panelHeight)) / 2); // 499x377 = art/intrface/invbox.frm

            addUI("background", new UI::Image("art/intrface/invbox.frm"));
            getUI("background")->mouseClickHandler().add(std::bind(&Inventory::backgroundRightClick, this, std::placeholders::_1));

            addUI("button_up",   new UI::ImageButton(UI::ImageButton::Type::INVENTORY_UP_ARROW,   128, 40));
            addUI("button_down", new UI::ImageButton(UI::ImageButton::Type::INVENTORY_DOWN_ARROW, 128, 65));
            auto buttonDownDisabled = new UI::Image("art/intrface/invdnds.frm");
            auto buttonUpDisabled = new UI::Image("art/intrface/invupds.frm");
            buttonUpDisabled->setPosition(Point(128, 40));
            buttonDownDisabled->setPosition(Point(128, 65));
            addUI("button_up_disabled", buttonUpDisabled);
            addUI("button_down_disabled", buttonDownDisabled);
            addUI("button_done", new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, 438, 328));

            getUI("button_done")->mouseClickHandler().add(std::bind(&Inventory::onDoneButtonClick, this, std::placeholders::_1));
            getUI("button_up")->mouseClickHandler().add(  std::bind(&Inventory::onScrollUpButtonClick, this, std::placeholders::_1));
            getUI("button_down")->mouseClickHandler().add(std::bind(&Inventory::onScrollDownButtonClick, this, std::placeholders::_1));

            // screen
            auto screenX = 300;
            auto screenY = 47;

            auto player = Game::getInstance()->player();

            addUI("player_name", new UI::TextArea(player->name(), screenX, screenY));

            auto line1 = new UI::Rectangle(Point(screenX, screenY+16), Graphics::Size(142, 1), {0x3f, 0xf8, 0x00, 0xff} );

            std::string statsLabels;
            for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
            {
                statsLabels += _t(MSG_INVENTORY, i) + "\n";
            }
            addUI("label_stats", new UI::TextArea(statsLabels, screenX, screenY + 10*2));

            std::string statsValues;
            for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
            {
                statsValues += std::to_string(player->stat((STAT)i)) + "\n";
            }
            addUI("label_stats_values", new UI::TextArea(statsValues, screenX + 22, screenY + 20));

            std::stringstream ss;
            for (unsigned int i=7; i<14; i++)
            {
                ss << _t(MSG_INVENTORY, i) << "\n";
            }
            auto textLabel = new UI::TextArea(ss.str(), screenX+40, screenY+20);

            // label: hit points
            ss.str("");
            ss << player->hitPoints();
            ss << "/";
            ss << player->hitPointsMax();
            auto hitPointsLabel = new UI::TextArea(ss.str(), screenX+94, screenY+20);
            hitPointsLabel->setWidth(46);
            hitPointsLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            // label: armor class
            ss.str("");
            ss << player->armorClass();
            auto armorClassLabel = new UI::TextArea(ss.str(), screenX+94, screenY+30);
            armorClassLabel->setWidth(46);
            armorClassLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

            // armorSlot, leftHand, rightHand
            Game::ArmorItemObject* armorSlot = player->armorSlot();
            Game::ItemObject* leftHand = player->leftHandSlot();
            Game::ItemObject* rightHand = player->rightHandSlot();


            // label: damage treshold levels
            ss.str("");
            if (armorSlot)
            {
                ss << player->damageThreshold(DAMAGE::NORMAL) + armorSlot->damageThreshold(DAMAGE::NORMAL) <<"/\n";
                ss << player->damageThreshold(DAMAGE::LASER) + armorSlot->damageThreshold(DAMAGE::LASER) <<"/\n";
                ss << player->damageThreshold(DAMAGE::FIRE) + armorSlot->damageThreshold(DAMAGE::FIRE) <<"/\n";
                ss << player->damageThreshold(DAMAGE::PLASMA) + armorSlot->damageThreshold(DAMAGE::PLASMA) <<"/\n";
                ss << player->damageThreshold(DAMAGE::EXPLOSIVE) + armorSlot->damageThreshold(DAMAGE::NORMAL) <<"/";
            }
            else
            {
                ss << player->damageThreshold(DAMAGE::NORMAL) <<"/\n";
                ss << player->damageThreshold(DAMAGE::LASER) <<"/\n";
                ss << player->damageThreshold(DAMAGE::FIRE) <<"/\n";
                ss << player->damageThreshold(DAMAGE::PLASMA) <<"/\n";
                ss << player->damageThreshold(DAMAGE::EXPLOSIVE) <<"/";
            }
            auto damageThresholdLabel = new UI::TextArea(ss.str(), screenX+94, screenY+40);
            damageThresholdLabel->setWidth(26);
            damageThresholdLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

            // label: damage resistance levels
            ss.str("");
            if (armorSlot)
            {
                ss << player->damageResist(DAMAGE::NORMAL) + armorSlot->damageResist(DAMAGE::NORMAL) <<"%\n";
                ss << player->damageResist(DAMAGE::LASER) + armorSlot->damageResist(DAMAGE::LASER) <<"%\n";
                ss << player->damageResist(DAMAGE::FIRE) + armorSlot->damageResist(DAMAGE::FIRE) <<"%\n";
                ss << player->damageResist(DAMAGE::PLASMA) + armorSlot->damageResist(DAMAGE::PLASMA) <<"%\n";
                ss << player->damageResist(DAMAGE::EXPLOSIVE) + armorSlot->damageResist(DAMAGE::NORMAL) <<"%";
            }
            else
            {
                ss << player->damageResist(DAMAGE::NORMAL) <<"%\n";
                ss << player->damageResist(DAMAGE::LASER) <<"%\n";
                ss << player->damageResist(DAMAGE::FIRE) <<"%\n";
                ss << player->damageResist(DAMAGE::PLASMA) <<"%\n";
                ss << player->damageResist(DAMAGE::EXPLOSIVE) <<"%";
            }
            auto damageResistanceLabel = new UI::TextArea(ss.str(), screenX+120, screenY+40);

            auto line2 = new UI::Rectangle(Point(screenX, screenY+94), Graphics::Size(142, 1), {0x3f, 0xf8, 0x00, 0xff} );
            auto line3 = new UI::Rectangle(Point(screenX, screenY+134), Graphics::Size(142, 1), {0x3f, 0xf8, 0x00, 0xff} );

            // label: Total Wt: (20)
            auto weight = player->carryWeight();
            auto weightMax = player->carryWeightMax();

            ss.str("");
            ss << weight;
            auto totalWtLabel = new UI::TextArea(_t(MSG_INVENTORY, 20), screenX+14, screenY+180);
            auto weightLabel = new UI::TextArea(ss.str(), screenX+70, screenY+180);
            weightLabel->setWidth(24);
            weightLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            ss.str("");
            ss << "/" << weightMax;
            auto weightMaxLabel = new UI::TextArea(ss.str(), screenX+94, screenY+180);
            if (weight>weightMax)
            {
                weightLabel->setFont("font1.aaf", {0xff, 0x00, 0x00, 0xff});
            }

            // label: left hand
            ss.str("");
            if (leftHand)
            {
                ss << _handItemSummary(leftHand);
            }
            auto leftHandLabel = new UI::TextArea(ss.str(), screenX, screenY+100);

            // label: right hand
            ss.str("");
            if (rightHand)
            {
                ss << _handItemSummary(rightHand);
            }
            auto rightHandLabel = new UI::TextArea(ss.str(), screenX, screenY+140);

            // screen info
            auto screenLabel = new UI::TextArea("", screenX, screenY+20);
            screenLabel->setSize({140, 168}); // screen size
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

            auto inventoryList = new UI::ItemsList(Point(40, 40));
            inventoryList->setItems(game->player()->inventory());
            addUI("inventory_list", inventoryList);

            // BIG ICONS
            // icon: armor
            {
                auto inventoryItem = new UI::InventoryItem(armorSlot, {154, 183});
                inventoryItem->setType(UI::InventoryItem::Type::SLOT);
                inventoryItem->itemDragStopHandler().add([inventoryList](Event::Mouse* event){ inventoryList->onItemDragStop(event); });
                inventoryList->itemDragStopHandler().add([inventoryItem](Event::Mouse* event){ inventoryItem->onArmorDragStop(event); });
                addUI(inventoryItem);
            }

            // icon: left hand
            {
                auto inventoryItem = new UI::InventoryItem(leftHand, {154, 286});
                inventoryItem->setType(UI::InventoryItem::Type::SLOT);
                inventoryItem->itemDragStopHandler().add([inventoryList](Event::Mouse* event){ inventoryList->onItemDragStop(event, HAND::LEFT); });
                inventoryList->itemDragStopHandler().add([inventoryItem](Event::Mouse* event){ inventoryItem->onHandDragStop(event, HAND::LEFT); });
                addUI(inventoryItem);
            }

            // icon: right hand
            {
                auto inventoryItem = new UI::InventoryItem(rightHand, {247, 286});
                inventoryItem->setType(UI::InventoryItem::Type::SLOT);
                inventoryItem->itemDragStopHandler().add([inventoryList](Event::Mouse* event){ inventoryList->onItemDragStop(event, HAND::RIGHT); });
                inventoryList->itemDragStopHandler().add([inventoryItem](Event::Mouse* event){ inventoryItem->onHandDragStop(event, HAND::RIGHT); });
                addUI(inventoryItem);
            }

            //initialize inventory scroll buttons
            enableScrollUpButton(false);
            if(inventoryList->canScrollDown())
            {
                enableScrollDownButton(true);
            }
            else
            {
                enableScrollDownButton(false);
            }

            inventoryList->itemsListModifiedHandler().add([this](Event::Event* event){ this->onInventoryModified(); });
        }

        void Inventory::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void Inventory::onScrollUpButtonClick(Event::Mouse* event)
        {
            auto inventory = dynamic_cast<UI::ItemsList*>(getUI("inventory_list"));
            if(inventory->canScrollUp())
            {
                inventory->scrollUp();
                //enable/disable scroll buttons on upward scroll
                if(!inventory->canScrollUp())
                {
                    enableScrollUpButton(false);
                }
                if(inventory->canScrollDown())
                {
                    enableScrollDownButton(true);
                }
            }
        }

        void Inventory::onScrollDownButtonClick(Event::Mouse* event)
        {
            auto inventory = dynamic_cast<UI::ItemsList*>(getUI("inventory_list"));
            if(inventory->canScrollDown())
            {
                inventory->scrollDown();
                //enable/disable scroll buttons on downward scroll
                if(!inventory->canScrollDown())
                {
                    enableScrollDownButton(false);
                }
                if(inventory->canScrollUp())
                {
                    enableScrollUpButton(true);
                }
            }
        }

        void Inventory::onInventoryModified()
        {
            auto inventory = dynamic_cast<UI::ItemsList*>(getUI("inventory_list"));
            /*
            this would scroll up when an item is removed and you are at the bottom
            of the list to fix the gap, but a bug is causing slotOffset to be crazy number
            if(inventory->items()->size() - inventory->slotOffset() <  inventory->slotsNumber())
            {
                inventory->scrollUp();
            }
            */
            enableScrollDownButton(inventory->canScrollDown());
            enableScrollUpButton(inventory->canScrollUp());
        }

        void Inventory::enableScrollUpButton(bool enable)
        {
            auto scrollUpButton = dynamic_cast<UI::ImageButton*>(getUI("button_up"));
            auto scrollUpButtonDisabled = dynamic_cast<UI::Image*>(getUI("button_up_disabled"));
            scrollUpButtonDisabled->setVisible(!enable);
            scrollUpButton->setEnabled(enable);
        }

        void Inventory::enableScrollDownButton(bool enable)
        {
            auto scrollDownButton = dynamic_cast<UI::ImageButton*>(getUI("button_down"));
            auto scrollDownButtonDisabled = dynamic_cast<UI::Image*>(getUI("button_down_disabled"));
            scrollDownButtonDisabled->setVisible(!enable);
            scrollDownButton->setEnabled(enable);
        }

        void Inventory::onArmorSlotMouseDown(Event::Mouse* event)
        {
            if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HAND)
            {
                auto itemUi = dynamic_cast<UI::ImageList*>(event->target());
                Game::getInstance()->pushState(new InventoryDragItem(itemUi));
            }
            else
            {
                auto itemPID = Game::getInstance()->player()->armorSlot()->PID();
                _screenShow(itemPID);
            }
        }

        void Inventory::onLeftHandSlotMouseDown(Event::Mouse* event)
        {
            if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HAND)
            {
                auto itemUi = dynamic_cast<UI::ImageList*>(event->target());
                Game::getInstance()->pushState(new InventoryDragItem(itemUi));
            }
            else
            {
                auto itemPID = Game::getInstance()->player()->leftHandSlot()->PID();
                _screenShow(itemPID);
            }
        }

        void Inventory::onRightHandSlotMouseDown(Event::Mouse* event)
        {
            if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HAND)
            {
                auto itemUi = dynamic_cast<UI::ImageList*>(event->target());
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
        //    auto itemUi = dynamic_cast<ImageList*>(event->target());
        //    itemUi->setCurrentImage(1);
        //    itemUi->setX(event->x() - itemUi->width()*0.5);
        //    itemUi->setY(event->y() - itemUi->height()*0.5);
        //}

        //void Inventory::onSlotMouseUp(MouseEvent* event)
        //{
        //    auto itemUi = dynamic_cast<ImageList*>(event->target());
        //    itemUi->setCurrentImage(0);
        //    itemUi->setX(event->x() - itemUi->width()*0.5);
        //    itemUi->setY(event->y() - itemUi->height()*0.5);
        //}

        //void Inventory::onSlotDrag(MouseEvent* event)
        //{
        //    //auto item = dynamic_cast<GameItemObject*>(event->reciever());
        //    auto itemUi = dynamic_cast<ImageList*>(event->target());
        //    //auto dragUi = item->inventoryDragUi();
        //    itemUi->setX(itemUi->x() + event->xOffset());
        //    itemUi->setY(itemUi->y() + event->yOffset());
        //    //Game::getInstance()->states()->back()->ui()->push_back(dragUi);
        //}

        std::string Inventory::_handItemSummary (Game::ItemObject* hand)
        {
            std::stringstream ss;
            if (hand)
            {
                ss << hand->name() << "\n";
                // is it weapon
                if (hand->subtype() == Game::ItemObject::Subtype::WEAPON)
                {
                    auto weapon = dynamic_cast<Game::WeaponItemObject*>(hand);
                    ss << "Dmg: " << weapon->damageMin() << "-" << weapon->damageMax() << " ";
                    ss << "Rng: " << weapon->rangePrimary();
                    // has it ammo?
                    if (weapon->ammoType() != 0)
                    {
                        ss << "\nAmmo: /" << weapon->ammoCapacity() << " ";
                        auto ammo = Game::ObjectFactory::getInstance()->createObject(weapon->ammoPID());
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

        void Inventory::backgroundRightClick(Event::Mouse* event)
        {
            auto mouse = Game::getInstance()->mouse();
            if (mouse->state() == Input::Mouse::Cursor::ACTION)
            {
                mouse->pushState(Input::Mouse::Cursor::HAND);
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
            auto line2 = getUI("line2");
            auto line3 = getUI("line3");
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
                playerNameLabel->setText(_t(MSG_PROTO_ITEMS, PID*100)); // item name
                screenLabel->setText(_t(MSG_PROTO_ITEMS, PID*100 + 1)); // item dedcription
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

        void Inventory::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    Game::getInstance()->popState();
                    break;
            }
        }
    }
}
