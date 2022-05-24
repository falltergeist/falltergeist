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

        CritterBarter::CritterBarter(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            Game::CritterObject* trader
        ) : State(mouse), _trader(trader), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
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
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(false);

            setPosition((Game::Game::getInstance()->renderer()->size() - Graphics::Point(640, 480)) / 2 + Graphics::Point(0, 291));

            addUI("background", _resourceManager->getImage("art/intrface/barter.frm"));

            auto dude = Game::Game::getInstance()->player();

            Helpers::CritterHelper critterHelper;
            Graphics::CritterAnimationFactory animationFactory;

            auto dudeCritter = animationFactory.buildStandingAnimation(
                critterHelper.armorFID(dude.get()),
                critterHelper.weaponId(dude.get()),
                Game::Orientation::SC
            );
            dudeCritter->setPosition({30, 45});
            addUI(dudeCritter.release());

            auto traderCritter = animationFactory.buildStandingAnimation(
                critterHelper.armorFID(_trader),
                critterHelper.weaponId(_trader),
                Game::Orientation::SC
            );
            traderCritter->setPosition({ 580, 45 });
            addUI(traderCritter.release());

            auto reaction = new UI::TextArea("", 140, -62);
            reaction->setSize({375, 53});
            reaction->setPadding({0, 5}, {0, 5});
            addUI("reaction", reaction);

            addUI("offerButton", _imageButtonFactory->getByType(ImageButtonType::DIALOG_RED_BUTTON, {40, 162}));
            getUI("offerButton")->mouseClickHandler().add(std::bind(&CritterBarter::onOfferButtonClick, this, std::placeholders::_1));

            addUI("talkButton", _imageButtonFactory->getByType(ImageButtonType::DIALOG_RED_BUTTON, {583, 162}));
            getUI("talkButton")->mouseClickHandler().add(std::bind(&CritterBarter::onTalkButtonClick, this, std::placeholders::_1));

            auto scrollUp = [](UI::ItemsList *list) {
                if (list->canScrollUp()) {
                    list->scrollUp();
                }
            };
            auto scrollDown = [](UI::ItemsList *list) {
                if (list->canScrollDown()) {
                    list->scrollDown();
                }
            };

            auto mineList = new UI::ItemsList({ 104, 35 });
            mineList->setSlotsNumber(3);
            mineList->setItems(Game::Game::getInstance()->player()->inventory());
            addUI("mineList", mineList);

            auto mineInventoryScrollUpButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_UP_ARROW, {190, 56});
            mineInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(mineList); });
            addUI(mineInventoryScrollUpButton);

            auto mineInventoryScrollDownButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_DOWN_ARROW, {190, 82});
            mineInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(mineList); });
            addUI(mineInventoryScrollDownButton);

            auto sellList = new UI::ItemsList({ 244, 20 });
            sellList->setItems(&_itemsToSell);
            sellList->setSlotsNumber(3);
            addUI("sellList", sellList);

            auto sellInventoryScrollUpButton = _imageButtonFactory->getByType(ImageButtonType::INVENTORY_UP_ARROW, {208, 114});
            sellInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(sellList); });
            addUI(sellInventoryScrollUpButton);

            auto sellInventoryScrollDownButton = _imageButtonFactory->getByType(ImageButtonType::INVENTORY_DOWN_ARROW, {208, 137});
            sellInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(sellList); });
            addUI(sellInventoryScrollDownButton);

            auto theirsList = new UI::ItemsList({ 470, 35 });
            theirsList->setItems(trader()->inventory());
            theirsList->setSlotsNumber(3);
            addUI("theirsList", theirsList);

            auto theirsInventoryScrollUpButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_UP_ARROW, {421, 56});
            theirsInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(theirsList); });
            addUI(theirsInventoryScrollUpButton);

            auto theirsInventoryScrollDownButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_DOWN_ARROW, {421, 82});
            theirsInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(theirsList); });
            addUI(theirsInventoryScrollDownButton);

            auto buyList = new UI::ItemsList({ 330, 20 });
            buyList->setItems(&_itemsToBuy);
            buyList->setSlotsNumber(3);
            addUI("buyList", buyList);

            auto buyInventoryScrollUpButton = _imageButtonFactory->getByType(ImageButtonType::INVENTORY_UP_ARROW, {413, 114});
            buyInventoryScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(buyList); });
            addUI(buyInventoryScrollUpButton);

            auto buyInventoryScrollDownButton = _imageButtonFactory->getByType(ImageButtonType::INVENTORY_DOWN_ARROW, {413, 137});
            buyInventoryScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(buyList); });
            addUI(buyInventoryScrollDownButton);

            auto sellPriceText = new UI::TextArea("$0", 246, 168);
            sellPriceText->setColor({ 255, 255, 255, 0 });
            addUI("sellPriceText", sellPriceText);

            auto buyPriceText = new UI::TextArea("$0", 334, 168);
            buyPriceText->setColor({ 255, 255, 255, 0 });
            addUI("buyPriceText", buyPriceText);

            mineList->itemDragStopHandler().add([sellList, mineList](Event::Mouse* event){ sellList->onItemDragStop(event, mineList); });
            sellList->itemDragStopHandler().add([mineList, sellList](Event::Mouse* event){ mineList->onItemDragStop(event, sellList); });
            sellList->itemsListModifiedHandler().add([this, sellPriceText](Event::Event*)
                {
                    _sellPriceTotal = 0;
                    for (const auto &v : _itemsToSell) {
                        _sellPriceTotal += v->price() * v->amount();
                    }
                    sellPriceText->setText("$" + std::to_string(_sellPriceTotal));
                });

            theirsList->itemDragStopHandler().add([buyList, theirsList](Event::Mouse* event){ buyList->onItemDragStop(event, theirsList); });
            buyList->itemDragStopHandler().add([theirsList, buyList](Event::Mouse* event){ theirsList->onItemDragStop(event, buyList); });
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
            dynamic_cast<UI::ItemsList*>(getUI("mineList"))->setItems(Game::Game::getInstance()->player()->inventory());
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

                    for (const auto &v : _itemsToSell) {
                        _trader->inventory()->push_back(v);
                    }

                    for (const auto &v : _itemsToBuy) {
                        Game::Game::getInstance()
                            ->player()
                            ->inventory()
                            ->push_back(v);
                    }

                    resetTransaction();

                } else {
                    reaction->setText(_t(MSG_INVENTORY, 28));
                }

            }
            catch (const Exception &) {}
        }

        void CritterBarter::onTalkButtonClick(Event::Mouse*)
        {
            if (auto interact = dynamic_cast<CritterInteract*>(Game::Game::getInstance()->topState(1))) {
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

        void CritterBarter::onStateDeactivate(Event::State* event)
        {
            for (const auto &v : _itemsToSell) {
                Game::Game::getInstance()->player()->inventory()->push_back(v);
            }

            for (const auto &v : _itemsToBuy) {
                _trader->inventory()->push_back(v);
            }

            dynamic_cast<UI::TextArea*>(getUI("reaction"))->setText("");

            resetTransaction();
        }

        Game::CritterObject *CritterBarter::trader() const
        {
            return _trader;
        }
    }
}
