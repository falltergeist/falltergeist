#include "../State/CritterBarter.h"
#include "../functions.h"
#include "../Exception.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/CritterAnimationFactory.h"
#include "../Helpers/CritterHelper.h"
#include "../State/CritterInteract.h"
#include "../UI/Animation.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ItemsList.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

        CritterBarter::CritterBarter(std::shared_ptr<UI::IResourceManager> _resourceManager) :
            State{},
            resourceManager{std::move(_resourceManager)},
            imageButtonFactory{std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager)}
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

            addUI("background", resourceManager->getImage("art/intrface/barter.frm"));

            auto dude = Game::getInstance()->player();

            Helpers::CritterHelper critterHelper;
            Graphics::CritterAnimationFactory animationFactory;

            {
                auto dudeCritter = animationFactory.buildStandingAnimation(
                        critterHelper.armorFID(dude.get()),
                        critterHelper.weaponId(dude.get()),
                        Game::Orientation::SC
                );
                dudeCritter->setPosition({30, 45});
                addUI(std::move(dudeCritter));
            }

            {
                auto traderCritter = animationFactory.buildStandingAnimation(
                        critterHelper.armorFID(_trader),
                        critterHelper.weaponId(_trader),
                        Game::Orientation::SC
                );
                traderCritter->setPosition({ 580, 45 });
                addUI(std::move(traderCritter));
            }

            {
                auto reaction = std::make_unique<UI::TextArea>("", 140, -62);
                reaction->setSize({375, 53});
                reaction->setPadding({0, 5}, {0, 5});
                addUI("reaction", std::move(reaction));
            }

            addUI("offerButton", imageButtonFactory->getByType(ImageButtonType::DIALOG_RED_BUTTON, {40, 162}));
            getUI("offerButton")->mouseClickHandler().add(std::bind(&CritterBarter::onOfferButtonClick, this, std::placeholders::_1));

            addUI("talkButton", imageButtonFactory->getByType(ImageButtonType::DIALOG_RED_BUTTON, {583, 162}));
            getUI("talkButton")->mouseClickHandler().add(std::bind(&CritterBarter::onTalkButtonClick, this, std::placeholders::_1));

            auto scrollUp = [](UI::ItemsList& list) {
                if (list.canScrollUp()) {
                    list.scrollUp();
                }
            };
            auto scrollDown = [](UI::ItemsList& list) {
                if (list.canScrollDown()) {
                    list.scrollDown();
                }
            };

            auto mineList = std::shared_ptr<UI::ItemsList>{new UI::ItemsList({ 104, 35 })};
            mineList->setSlotsNumber(3);
            mineList->setItems(Game::getInstance()->player()->inventory());
            addSharedUI("mineList", mineList);

            {
                auto mineInventoryScrollUpButton = imageButtonFactory->getByType(ImageButtonType::DIALOG_UP_ARROW, {190, 56});
                mineInventoryScrollUpButton->mouseClickHandler().add([=](...) {
                    scrollUp(*mineList);
                });
                addUI(std::move(mineInventoryScrollUpButton));
            }

            {
                auto mineInventoryScrollDownButton = imageButtonFactory->getByType(ImageButtonType::DIALOG_DOWN_ARROW, {190, 82});
                mineInventoryScrollDownButton->mouseClickHandler().add([=](...) {
                    scrollDown(*mineList);
                });
                addUI(std::move(mineInventoryScrollDownButton));
            }

            auto sellList = std::shared_ptr<UI::ItemsList>{new UI::ItemsList({ 244, 20 })};
            sellList->setItems(&_itemsToSell);
            sellList->setSlotsNumber(3);
            addSharedUI("sellList", sellList);

            {
                auto sellInventoryScrollUpButton = imageButtonFactory->getByType(ImageButtonType::INVENTORY_UP_ARROW, {208, 114});
                sellInventoryScrollUpButton->mouseClickHandler().add([=](...) {
                    scrollUp(*sellList);
                });
                addUI(std::move(sellInventoryScrollUpButton));
            }

            {
                auto sellInventoryScrollDownButton = imageButtonFactory->getByType(ImageButtonType::INVENTORY_DOWN_ARROW, {208, 137});
                sellInventoryScrollDownButton->mouseClickHandler().add([=](...) {
                    scrollDown(*sellList);
                });
                addUI(std::move(sellInventoryScrollDownButton));
            }

            auto theirsList = std::shared_ptr<UI::ItemsList>{new UI::ItemsList({ 470, 35 })};
            theirsList->setItems(trader()->inventory());
            theirsList->setSlotsNumber(3);
            addSharedUI("theirsList", theirsList);

            {
                auto theirsInventoryScrollUpButton = imageButtonFactory->getByType(ImageButtonType::DIALOG_UP_ARROW, {421, 56});
                theirsInventoryScrollUpButton->mouseClickHandler().add([=](...) {
                    scrollUp(*theirsList);
                });
                addUI(std::move(theirsInventoryScrollUpButton));
            }

            {
                auto theirsInventoryScrollDownButton = imageButtonFactory->getByType(ImageButtonType::DIALOG_DOWN_ARROW, {421, 82});
                theirsInventoryScrollDownButton->mouseClickHandler().add([=](...) {
                    scrollDown(*theirsList);
                });
                addUI(std::move(theirsInventoryScrollDownButton));
            }

            auto buyList = std::shared_ptr<UI::ItemsList>{new UI::ItemsList({ 330, 20 })};
            buyList->setItems(&_itemsToBuy);
            buyList->setSlotsNumber(3);
            addSharedUI("buyList", buyList);

            {
                auto buyInventoryScrollUpButton = imageButtonFactory->getByType(ImageButtonType::INVENTORY_UP_ARROW, {413, 114});
                buyInventoryScrollUpButton->mouseClickHandler().add([=](...) {
                    scrollUp(*buyList);
                });
                addUI(std::move(buyInventoryScrollUpButton));
            }

            {
                auto buyInventoryScrollDownButton = imageButtonFactory->getByType(ImageButtonType::INVENTORY_DOWN_ARROW, {413, 137});
                buyInventoryScrollDownButton->mouseClickHandler().add([=](...) {
                    scrollDown(*buyList);
                });
                addUI(std::move(buyInventoryScrollDownButton));
            }

            {
                auto& sellPriceText = makeNamedUI<UI::TextArea>("sellPriceText","$0", 246, 168);
                sellPriceText.setColor({255, 255, 255, 0});
                sellList->itemsListModifiedHandler().add([&](Event::Event*) {
                    _sellPriceTotal = 0;
                    for (const auto &v : _itemsToSell) {
                        _sellPriceTotal += v->price() * v->amount();
                    }
                    sellPriceText.setText("$" + std::to_string(_sellPriceTotal));
                });
            }

            {
                auto& buyPriceText = makeNamedUI<UI::TextArea>("buyPriceText", "$0", 334, 168);
                buyPriceText.setColor({ 255, 255, 255, 0 });
                buyList->itemsListModifiedHandler().add([&](Event::Event*) {
                    _buyPriceTotal = 0;
                    for (const auto &v : _itemsToBuy) {
                        // TODO: apply barter skill + Master Trader perk + Reaction (mood?) modifier
                        _buyPriceTotal += v->price() * v->amount();
                    }
                    buyPriceText.setText("$" + std::to_string(_buyPriceTotal));
                });
            }

            mineList->itemDragStopHandler().add([=](Event::Mouse* event){
                sellList->onItemDragStop(event);
            });
            sellList->itemDragStopHandler().add([=](Event::Mouse* event){
                mineList->onItemDragStop(event);
            });
            theirsList->itemDragStopHandler().add([=](Event::Mouse* event){
                buyList->onItemDragStop(event);
            });
            buyList->itemDragStopHandler().add([=](Event::Mouse* event){
                theirsList->onItemDragStop(event);
            });
        }

        void CritterBarter::resetTransaction()
        {
            getUI<UI::TextArea>("sellPriceText")->setText("$0");
            getUI<UI::TextArea>("buyPriceText")->setText("$0");

            _itemsToSell.clear();
            getUI<UI::ItemsList>("mineList")->setItems(Game::getInstance()->player()->inventory());
            getUI<UI::ItemsList>("sellList")->setItems(&_itemsToSell);

            _itemsToBuy.clear();
            getUI<UI::ItemsList>("theirsList")->setItems(_trader->inventory());
            getUI<UI::ItemsList>("buyList")->setItems(&_itemsToBuy);

            _sellPriceTotal = 0;
            _buyPriceTotal = 0;
        }

        void CritterBarter::onOfferButtonClick(Event::Mouse*)
        {
            auto reaction = getUI<UI::TextArea>("reaction");

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
            if (auto interact = dynamic_cast<CritterInteract*>(&Game::getInstance()->topState(1))) {
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

            getUI<UI::TextArea>("reaction")->setText("");

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
