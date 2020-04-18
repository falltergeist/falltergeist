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
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        Inventory::Inventory(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);

            pushHandler().add([](Event::State* ev) {
                Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::ACTION);
            });
            popHandler().add([](Event::State* ev) {
                // If hand cursor now
                if (Game::getInstance()->mouse()->state() == Input::Mouse::Cursor::HAND) {
                    Game::getInstance()->mouse()->popState();
                }
                Game::getInstance()->mouse()->popState();
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

            auto game = Game::getInstance();
            auto panelHeight = Game::getInstance()->locationState()->playerPanel()->size().height();

            setPosition((game->renderer()->size() - Point(499, 377 + panelHeight)) / 2); // 499x377 = art/intrface/invbox.frm

            addUI("background", resourceManager->getImage("art/intrface/invbox.frm"))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->backgroundRightClick(e);
                });

            addUI("button_up",   imageButtonFactory->getByType(ImageButtonType::INVENTORY_UP_ARROW,   {128, 40}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onScrollUpButtonClick(e);
                });

            addUI("button_down", imageButtonFactory->getByType(ImageButtonType::INVENTORY_DOWN_ARROW, {128, 65}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onScrollDownButtonClick(e);
                });

            addUI("button_up_disabled", resourceManager->getImage("art/intrface/invdnds.frm"))
                ->setPosition({128, 40});

            addUI("button_down_disabled", resourceManager->getImage("art/intrface/invupds.frm"))
                ->setPosition({128, 65});

            addUI("button_done", imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {438, 328}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onDoneButtonClick(e);
                });

            const UI::Point screenPos{300, 47};
            auto player = Game::getInstance()->player();

            makeNamedUI<UI::TextArea>("player_name", player->name(), screenPos);

            // line
            makeUI<UI::Rectangle>(screenPos.add({0, 16}), Graphics::Size{142, 1}, SDL_Color{0x3f, 0xf8, 0x00, 0xff});

            {
                std::string statsLabels;
                for (auto i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
                {
                    statsLabels += _t(MSG_INVENTORY, i) + "\n";
                }
                makeNamedUI<UI::TextArea>("label_stats", std::move(statsLabels), screenPos.add({0, 20}));
            }

            {
                std::string statsValues;
                for (auto i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
                {
                    statsValues += std::to_string(player->stat((STAT)i)) + "\n";
                }
                makeNamedUI<UI::TextArea>("label_stats_values", std::move(statsValues), screenPos.add({22, 20}));
            }

            {
                std::string txt;
                for (unsigned int i=7; i<14; i++)
                {
                    txt += _t(MSG_INVENTORY, i) + "\n";
                }
                makeNamedUI<UI::TextArea>("textLabel", std::move(txt), screenPos.add({40, 20}));
            }

            // label: hit points
            {
                std::stringstream ss;
                ss << player->hitPoints();
                ss << "/";
                ss << player->hitPointsMax();
                auto& hpui = *makeNamedUI<UI::TextArea>("hitPointsLabel", ss.str(), screenPos.add({94, 20}));
                hpui.setWidth(46);
                hpui.setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            }

            // label: armor class
            {
                std::stringstream ss;
                ss << player->armorClass();
                auto& armorClassLabel = *makeNamedUI<UI::TextArea>("armorClassLabel", ss.str(), screenPos.add({94, 30}));
                armorClassLabel.setWidth(46);
                armorClassLabel.setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            }

            Game::ArmorItemObject* playerArmor = player->armorSlot();

            // label: damage threshold levels
            {
                std::stringstream ss;
                if (playerArmor)
                {
                    ss << player->damageThreshold(DAMAGE::NORMAL) + playerArmor->damageThreshold(DAMAGE::NORMAL) << "/\n";
                    ss << player->damageThreshold(DAMAGE::LASER) + playerArmor->damageThreshold(DAMAGE::LASER) << "/\n";
                    ss << player->damageThreshold(DAMAGE::FIRE) + playerArmor->damageThreshold(DAMAGE::FIRE) << "/\n";
                    ss << player->damageThreshold(DAMAGE::PLASMA) + playerArmor->damageThreshold(DAMAGE::PLASMA) << "/\n";
                    ss << player->damageThreshold(DAMAGE::EXPLOSIVE) + playerArmor->damageThreshold(DAMAGE::NORMAL) << "/";
                }
                else
                {
                    ss << player->damageThreshold(DAMAGE::NORMAL) <<"/\n";
                    ss << player->damageThreshold(DAMAGE::LASER) <<"/\n";
                    ss << player->damageThreshold(DAMAGE::FIRE) <<"/\n";
                    ss << player->damageThreshold(DAMAGE::PLASMA) <<"/\n";
                    ss << player->damageThreshold(DAMAGE::EXPLOSIVE) <<"/";
                }
                auto& damageThresholdLabel = *makeNamedUI<UI::TextArea>("damageThresholdLabel", ss.str(), screenPos.add({94, 40}));
                damageThresholdLabel.setWidth(26);
                damageThresholdLabel.setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            }

            // label: damage resistance levels
            {
                std::stringstream ss;
                if (playerArmor)
                {
                    ss << player->damageResist(DAMAGE::NORMAL) + playerArmor->damageResist(DAMAGE::NORMAL) << "%\n";
                    ss << player->damageResist(DAMAGE::LASER) + playerArmor->damageResist(DAMAGE::LASER) << "%\n";
                    ss << player->damageResist(DAMAGE::FIRE) + playerArmor->damageResist(DAMAGE::FIRE) << "%\n";
                    ss << player->damageResist(DAMAGE::PLASMA) + playerArmor->damageResist(DAMAGE::PLASMA) << "%\n";
                    ss << player->damageResist(DAMAGE::EXPLOSIVE) + playerArmor->damageResist(DAMAGE::NORMAL) << "%";
                }
                else
                {
                    ss << player->damageResist(DAMAGE::NORMAL) <<"%\n";
                    ss << player->damageResist(DAMAGE::LASER) <<"%\n";
                    ss << player->damageResist(DAMAGE::FIRE) <<"%\n";
                    ss << player->damageResist(DAMAGE::PLASMA) <<"%\n";
                    ss << player->damageResist(DAMAGE::EXPLOSIVE) <<"%";
                }
                auto damageResistanceLabel = makeNamedUI<UI::TextArea>("damageResistanceLabel", ss.str(), screenPos.add({120, 40}));
            }

            makeNamedUI<UI::Rectangle>(
                    "line2",
                    screenPos.add({0, 94}),
                    Graphics::Size(142, 1),
                    SDL_Color{0x3f, 0xf8, 0x00, 0xff});

            makeNamedUI<UI::Rectangle>(
                    "line3",
                    screenPos.add({0, 134}),
                    Graphics::Size(142, 1),
                    SDL_Color{0x3f, 0xf8, 0x00, 0xff});

            auto weight = player->carryWeight();
            auto weightMax = player->carryWeightMax();

            makeNamedUI<UI::TextArea>(
                    "totalWtLabel",
                    _t(MSG_INVENTORY, 20),
                    screenPos.add({14, 180}));

            // label: weight
            {
                auto& weightLabel = *makeNamedUI<UI::TextArea>(
                        "weightLabel",
                        std::to_string(weight),
                        screenPos.add({70, 180}));
                weightLabel.setWidth(24);
                weightLabel.setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
                if (weight > weightMax)
                {
                    weightLabel.setFont("font1.aaf", {0xff, 0x00, 0x00, 0xff});
                }
            }

            // label: weight max
            {
                std::stringstream ss;
                ss << weight;
                ss.str("");
                ss << "/" << weightMax;
                makeNamedUI<UI::TextArea>("weightMaxLabel", ss.str(), screenPos.add({94, 180}));
            }

            Game::ItemObject* leftHand = player->leftHandSlot();

            makeNamedUI<UI::TextArea>(
                    "leftHandLabel",
                    leftHand ? _handItemSummary(leftHand) : "",
                    screenPos.add({0, 100}));

            Game::ItemObject* rightHand = player->rightHandSlot();

            makeNamedUI<UI::TextArea>(
                    "rightHandLabel",
                    rightHand ? _handItemSummary(rightHand) : "",
                    screenPos.add({0, 140}));

            // screen info
            {
                auto& screenLabel = *makeNamedUI<UI::TextArea>(
                        "screenLabel",
                        "",
                        screenPos.add({0, 20}));
                screenLabel.setSize({140, 168}); // screen size
                screenLabel.setVisible(false);
                screenLabel.setWordWrap(true);
            }

            auto& inventoryList = *makeNamedUI<UI::ItemsList>("inventory_list", Point{40, 40});
            inventoryList.setItems(game->player()->inventory());

            // TODO: this is a rotating animation in the vanilla engine
            auto dude = Game::getInstance()->player();

            {
                Helpers::CritterHelper critterHelper;
                Graphics::CritterAnimationFactory animationFactory;

                addUI(animationFactory.buildStandingAnimation(
                        critterHelper.armorFID(dude.get()),
                        critterHelper.weaponId(dude.get()),
                        Game::Orientation::SC
                ))->setPosition({188, 52});
            }

            // BIG ICONS

            // icon: armor
            {
                auto& inventoryItem = *makeUI<UI::InventoryItem>(playerArmor, Point{154, 183});
                inventoryItem.setType(UI::InventoryItem::Type::SLOT);
                inventoryItem.itemDragStopHandler().add([&](Event::Mouse* event){
                    inventoryList.onItemDragStop(event);
                });
                inventoryList.itemDragStopHandler().add([&](Event::Mouse* event){
                    inventoryItem.onArmorDragStop(event);
                });
            }

            // icon: left hand
            {
                auto& inventoryItem = *makeUI<UI::InventoryItem>(leftHand, Point{154, 286});
                inventoryItem.setType(UI::InventoryItem::Type::SLOT);
                inventoryItem.itemDragStopHandler().add([&](Event::Mouse* event){
                    inventoryList.onItemDragStop(event, HAND::LEFT);
                });
                inventoryList.itemDragStopHandler().add([&](Event::Mouse* event){
                    inventoryItem.onHandDragStop(event, HAND::LEFT);
                });
            }

            // icon: right hand
            {
                auto& inventoryItem = *makeUI<UI::InventoryItem>(rightHand, Point{247, 286});
                inventoryItem.setType(UI::InventoryItem::Type::SLOT);
                inventoryItem.itemDragStopHandler().add([&](Event::Mouse* event){
                    inventoryList.onItemDragStop(event, HAND::RIGHT);
                });
                inventoryList.itemDragStopHandler().add([&](Event::Mouse* event){
                    inventoryItem.onHandDragStop(event, HAND::RIGHT);
                });
            }

            //initialize inventory scroll buttons
            enableScrollUpButton(false);
            enableScrollDownButton(inventoryList.canScrollDown());

            inventoryList.itemsListModifiedHandler().add([this](Event::Event* event){
                this->onInventoryModified();
            });
        }

        void Inventory::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void Inventory::onScrollUpButtonClick(Event::Mouse* event)
        {
            auto inventory = getUI<UI::ItemsList>("inventory_list");
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
            auto inventory = getUI<UI::ItemsList>("inventory_list");
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
            auto inventory = getUI<UI::ItemsList>("inventory_list");
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
            getUI<UI::ImageButton>("button_up")->setEnabled(enable);
            getUI<UI::Image>("button_up_disabled")->setVisible(not enable);
        }

        void Inventory::enableScrollDownButton(bool enable)
        {
            getUI<UI::ImageButton>("button_down")->setEnabled(enable);
            getUI<UI::Image>("button_down_disabled")->setVisible(not enable);
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
            auto playerNameLabel = getUI<UI::TextArea>("player_name");
            auto statsLabel = getUI<UI::TextArea>("label_stats");
            auto statsValuesLabel = getUI<UI::TextArea>("label_stats_values");
            auto textLabel = getUI<UI::TextArea>("textLabel");
            auto hitPointsLabel = getUI<UI::TextArea>("hitPointsLabel");
            auto armorClassLabel = getUI<UI::TextArea>("armorClassLabel");
            auto damageThresholdLabel = getUI<UI::TextArea>("damageThresholdLabel");
            auto damageResistanceLabel = getUI<UI::TextArea>("damageResistanceLabel");
            auto line2 = getUI("line2");
            auto line3 = getUI("line3");
            auto totalWtLabel = getUI<UI::TextArea>("totalWtLabel");
            auto weightLabel = getUI<UI::TextArea>("weightLabel");
            auto weightMaxLabel = getUI<UI::TextArea>("weightMaxLabel");
            auto leftHandLabel = getUI<UI::TextArea>("leftHandLabel");
            auto rightHandLabel = getUI<UI::TextArea>("rightHandLabel");
            auto screenLabel = getUI<UI::TextArea>("screenLabel");

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
