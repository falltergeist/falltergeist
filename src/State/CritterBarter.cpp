/*
 * Copyright 2012-2018 Falltergeist Developers.
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
#include "../State/CritterBarter.h"

// C++ standard includes

// Falltergeist includes
#include "../functions.h"
#include "../Exception.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
//#include "../State/CritterDialog.h"
#include "../State/CritterInteract.h"
#include "../UI/Animation.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ItemsList.h"
#include "../UI/TextArea.h"

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
            for (auto p : _itemsToSell) {
                delete p;
            }
            for (auto p : _itemsToBuy) {
                delete p;
            }
            _itemsToSell.clear();
            _itemsToBuy.clear();
        }

        void CritterBarter::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(false);

            setPosition((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2 + Point(0, 291));

            addUI("background", new UI::Image("art/intrface/barter.frm"));

            auto dudeCritter = Game::getInstance()->player()->generateAnimation("aa", Game::Orientation::SC);
            dudeCritter->setPosition({30, 45});
            addUI(dudeCritter);

            auto traderCritter = _trader->generateAnimation("aa", Game::Orientation::SC);
            traderCritter->setPosition({ 580, 45 });
            addUI(traderCritter);

            auto reaction = new UI::TextArea("", 140, -62);
            reaction->setSize({375, 53});
            reaction->setPadding({0, 5}, {0, 5});
            addUI("reaction", reaction);

            addUI("offerButton", new UI::ImageButton(UI::ImageButton::Type::DIALOG_RED_BUTTON, 40, 162));
            getUI("offerButton")->mouseClickHandler().add(std::bind(&CritterBarter::onOfferButtonClick, this, std::placeholders::_1));

            addUI("talkButton", new UI::ImageButton(UI::ImageButton::Type::DIALOG_RED_BUTTON, 583, 162));
            getUI("talkButton")->mouseClickHandler().add(std::bind(&CritterBarter::onTalkButtonClick, this, std::placeholders::_1));

            auto scrollUp = [](UI::ItemsList *list) { if (list->canScrollUp()) list->scrollUp(); };
            auto scrollDown = [](UI::ItemsList *list) { if (list->canScrollDown()) list->scrollDown(); };

            auto mineList = new UI::ItemsList({ 104, 35 });
            mineList->setSlotsNumber(3);
            mineList->setItems(Game::getInstance()->player()->inventory());
            addUI("mineList", mineList);

            auto mineInventoryScrollUpButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_UP_ARROW,   190, 56);
            mineInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(mineList); });
            addUI(mineInventoryScrollUpButton);

            auto mineInventoryScrollDownButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_DOWN_ARROW, 190, 82);
            mineInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(mineList); });
            addUI(mineInventoryScrollDownButton);

            auto sellList = new UI::ItemsList({ 244, 20 });
            sellList->setItems(&_itemsToSell);
            sellList->setSlotsNumber(3);
            addUI("sellList", sellList);

            auto sellInventoryScrollUpButton = new UI::ImageButton(UI::ImageButton::Type::INVENTORY_UP_ARROW,   208, 114);
            sellInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(sellList); });
            addUI(sellInventoryScrollUpButton);

            auto sellInventoryScrollDownButton = new UI::ImageButton(UI::ImageButton::Type::INVENTORY_DOWN_ARROW, 208, 137);
            sellInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(sellList); });
            addUI(sellInventoryScrollDownButton);

            auto theirsList = new UI::ItemsList({ 470, 35 });
            theirsList->setItems(trader()->inventory());
            theirsList->setSlotsNumber(3);
            addUI("theirsList", theirsList);

            auto theirsInventoryScrollUpButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_UP_ARROW,   421, 56);
            theirsInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(theirsList); });
            addUI(theirsInventoryScrollUpButton);

            auto theirsInventoryScrollDownButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_DOWN_ARROW, 421, 82);
            theirsInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(theirsList); });
            addUI(theirsInventoryScrollDownButton);

            auto buyList = new UI::ItemsList({ 330, 20 });
            buyList->setItems(&_itemsToBuy);
            buyList->setSlotsNumber(3);
            addUI("buyList", buyList);

            auto buyInventoryScrollUpButton = new UI::ImageButton(UI::ImageButton::Type::INVENTORY_UP_ARROW,   413, 114);
            buyInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(buyList); });
            addUI(buyInventoryScrollUpButton);

            auto buyInventoryScrollDownButton = new UI::ImageButton(UI::ImageButton::Type::INVENTORY_DOWN_ARROW, 413, 137);
            buyInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(buyList); });
            addUI(buyInventoryScrollDownButton);

            auto sellPriceText = new UI::TextArea("$0", 246, 168);
            sellPriceText->setColor({ 255, 255, 255, 0 });
            addUI("sellPriceText", sellPriceText);

            auto buyPriceText = new UI::TextArea("$0", 334, 168);
            buyPriceText->setColor({ 255, 255, 255, 0 });
            addUI("buyPriceText", buyPriceText);

            mineList->itemDragStopHandler().add([sellList](Event::Mouse* event){ sellList->onItemDragStop(event); });
            sellList->itemDragStopHandler().add([mineList](Event::Mouse* event){ mineList->onItemDragStop(event); });
            sellList->itemsListModifiedHandler().add([this, sellPriceText](Event::Event*)
                {
                    _sellPriceTotal = 0;
                    for (const auto &v : _itemsToSell) {
                        _sellPriceTotal += v->price() * v->amount();
                    }
                    sellPriceText->setText("$" + std::to_string(_sellPriceTotal));
                });

            theirsList->itemDragStopHandler().add([buyList](Event::Mouse* event){ buyList->onItemDragStop(event); });
            buyList->itemDragStopHandler().add([theirsList](Event::Mouse* event){ theirsList->onItemDragStop(event); });
            buyList->itemsListModifiedHandler().add([this, buyPriceText](Event::Event*)
                {
                    _buyPriceTotal = 0;
                    for (const auto &v : _itemsToBuy) {
                        // TODO: apply barter skill + Master Trader perk + Reaction (mood?) modifier
                        _buyPriceTotal += v->price() * v->amount();
                    }
                    buyPriceText->setText("$" + std::to_string(_buyPriceTotal));
                });

        }

        void CritterBarter::resetTransaction()
        {
            dynamic_cast<UI::TextArea*>(getUI("sellPriceText"))->setText("$0");
            dynamic_cast<UI::TextArea*>(getUI("buyPriceText"))->setText("$0");

            _itemsToSell.clear();
            dynamic_cast<UI::ItemsList*>(getUI("mineList"))->setItems(Game::getInstance()->player()->inventory());
            dynamic_cast<UI::ItemsList*>(getUI("sellList"))->setItems(&_itemsToSell);

            _itemsToBuy.clear();
            dynamic_cast<UI::ItemsList*>(getUI("theirsList"))->setItems(_trader->inventory());
            dynamic_cast<UI::ItemsList*>(getUI("buyList"))->setItems(&_itemsToBuy);

            _sellPriceTotal = 0;
            _buyPriceTotal = 0;
        }

        void CritterBarter::onOfferButtonClick(Event::Mouse*)
        {
            auto reaction = dynamic_cast<UI::TextArea*>(getUI("reaction"));

            try {
                if (_sellPriceTotal == 0 && _buyPriceTotal == 0) {
                    return;
                } else if (_sellPriceTotal >= _buyPriceTotal) {
                    reaction->setText(_t(MSG_INVENTORY, 27));

                    for (const auto &v : _itemsToSell)
                        _trader->inventory()->push_back(v);

                    for (const auto &v : _itemsToBuy)
                        Game::getInstance()->player()->inventory()->push_back(v);

                    resetTransaction();

                } else {
                    reaction->setText(_t(MSG_INVENTORY, 28));
                }

            }
            catch (const Exception &) {}
        }

        void CritterBarter::onTalkButtonClick(Event::Mouse*)
        {
            if (auto interact = dynamic_cast<CritterInteract*>(Game::getInstance()->topState(1))) {
                interact->switchSubState(CritterInteract::SubState::DIALOG);
            }
        }

        void CritterBarter::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    onTalkButtonClick(nullptr);
                    break;
            }
        }

        void CritterBarter::onStateDeactivate(Event::State*)
        {
            for (const auto &v : _itemsToSell)
                Game::getInstance()->player()->inventory()->push_back(v);

            for (const auto &v : _itemsToBuy)
                _trader->inventory()->push_back(v);

            dynamic_cast<UI::TextArea*>(getUI("reaction"))->setText("");

            resetTransaction();
        }

        Game::CritterObject *CritterBarter::trader()
        {
            return _trader;
        }

        void CritterBarter::setTrader(Game::CritterObject *trader)
        {
            _trader = trader;
        }
    }
}
