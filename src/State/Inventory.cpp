#include <sstream>
#include "../State/Inventory.h"
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
#include "../Graphics/CritterAnimationFactory.h"
#include "../Graphics/Size.h"
#include "../Helpers/CritterHelper.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/State.h"
#include "../State/GameMenu.h"
#include "../State/InventoryDragItem.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/InventoryItem.h"
#include "../UI/ItemsList.h"
#include "../UI/PlayerPanel.h"
#include "../UI/Rectangle.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        Inventory::Inventory(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            std::shared_ptr<ILogger> logger
        ) : State(mouse), _logger(logger), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);

            pushHandler().add([](Event::State* ev) {
                Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::ACTION);
            });
            popHandler().add([](Event::State* ev) {
                // If hand cursor now
                if (Game::Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HAND) {
                    Game::Game::getInstance()->mouse()->popState();
                }
                Game::Game::getInstance()->mouse()->popState();
            });
        }

        void Inventory::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(false);

            auto game = Game::Game::getInstance();
            auto panelHeight = Game::Game::getInstance()->locationState()->playerPanel()->size().height();

            setPosition((game->renderer()->size() - Point(499, 377 + panelHeight)) / 2); // 499x377 = art/intrface/invbox.frm

            addUI("background", _resourceManager->getImage("art/intrface/invbox.frm"));
            getUI("background")->mouseClickHandler().add(std::bind(&Inventory::backgroundRightClick, this, std::placeholders::_1));

            addUI("button_up",   _imageButtonFactory->getByType(ImageButtonType::INVENTORY_UP_ARROW,   {128, 40}));
            addUI("button_down", _imageButtonFactory->getByType(ImageButtonType::INVENTORY_DOWN_ARROW, {128, 65}));
            auto buttonDownDisabled = _resourceManager->getImage("art/intrface/invdnds.frm");
            auto buttonUpDisabled = _resourceManager->getImage("art/intrface/invupds.frm");
            buttonUpDisabled->setPosition(Point(128, 40));
            buttonDownDisabled->setPosition(Point(128, 65));
            addUI("button_up_disabled", buttonUpDisabled);
            addUI("button_down_disabled", buttonDownDisabled);
            addUI("button_done", _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {438, 328}));

            getUI("button_done")->mouseClickHandler().add(std::bind(&Inventory::onDoneButtonClick, this, std::placeholders::_1));
            getUI("button_up")->mouseClickHandler().add(  std::bind(&Inventory::onScrollUpButtonClick, this, std::placeholders::_1));
            getUI("button_down")->mouseClickHandler().add(std::bind(&Inventory::onScrollDownButtonClick, this, std::placeholders::_1));

            // screen
            auto screenX = 300;
            auto screenY = 47;

            auto player = Game::Game::getInstance()->player();

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

            // TODO: this is a rotating animation in the vanilla engine
            auto dude = Game::Game::getInstance()->player();

            Helpers::CritterHelper critterHelper;
            Graphics::CritterAnimationFactory animationFactory;

            auto dudeCritter = animationFactory.buildStandingAnimation(
                critterHelper.armorFID(dude.get()),
                critterHelper.weaponId(dude.get()),
                Game::Orientation::SC
            );
            dudeCritter->setPosition({188, 52});
            addUI(dudeCritter.release());

            // BIG ICONS
            // icon: armor
            {
                auto inventoryItem = new UI::InventoryItem(armorSlot, {154, 183});
                inventoryItem->setType(UI::InventoryItem::Type::SLOT);
                inventoryItem->itemDragStopHandler().add([inventoryList, inventoryItem](Event::Mouse* event){ inventoryList->onItemDragStop(event, inventoryItem); });
                inventoryList->itemDragStopHandler().add([inventoryItem, inventoryList](Event::Mouse* event){ inventoryItem->onArmorDragStop(event, inventoryList); });
                addUI(inventoryItem);
            }

            // icon: left hand
            {
                auto inventoryItem = new UI::InventoryItem(leftHand, {154, 286});
                inventoryItem->setType(UI::InventoryItem::Type::SLOT);
                inventoryItem->itemDragStopHandler().add([inventoryList, inventoryItem](Event::Mouse* event){ inventoryList->onItemDragStop(event, HAND::LEFT, inventoryItem); });
                inventoryList->itemDragStopHandler().add([inventoryItem, inventoryList](Event::Mouse* event){ inventoryItem->onHandDragStop(event, HAND::LEFT, inventoryList); });
                addUI(inventoryItem);
            }

            // icon: right hand
            {
                auto inventoryItem = new UI::InventoryItem(rightHand, {247, 286});
                inventoryItem->setType(UI::InventoryItem::Type::SLOT);
                inventoryItem->itemDragStopHandler().add([inventoryList, inventoryItem](Event::Mouse* event){ inventoryList->onItemDragStop(event, HAND::RIGHT, inventoryItem); });
                inventoryList->itemDragStopHandler().add([inventoryItem, inventoryList](Event::Mouse* event){ inventoryItem->onHandDragStop(event, HAND::RIGHT, inventoryList); });
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
            Game::Game::getInstance()->popState();
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

        std::string Inventory::_handItemSummary (Game::ItemObject* hand)
        {
            Game::ObjectFactory objectFactory(_logger);

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
                        auto ammo = objectFactory.createObjectByPID(weapon->ammoPID());
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
            auto mouse = Game::Game::getInstance()->mouse();
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
            auto player = Game::Game::getInstance()->player();
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
                    Game::Game::getInstance()->popState();
                    break;
            }
        }
        void Inventory::onStateActivate(Event::State* event) {
            _previousCursor = mouse()->cursor();
        }

        void Inventory::onStateDeactivate(Event::State* event) {
            mouse()->setCursor(_previousCursor);
        }
    }
}
