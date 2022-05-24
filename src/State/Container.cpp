#include "../State/Container.h"
#include "../ResourceManager.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/CritterAnimationFactory.h"
#include "../Graphics/Renderer.h"
#include "../Helpers/CritterHelper.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../UI/Animation.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ItemsList.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

        Container::Container(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            Game::ContainerItemObject* object
        ) : State(mouse), _object(object), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        void Container::init()
        {
            if (_initialized) {
                return;
            }

            setModal(true);
            setFullscreen(false);

            auto game = Game::Game::getInstance();

            setPosition((game->renderer()->size() - Graphics::Point(537, 376)) / 2);

            addUI("background", _resourceManager->getImage("art/intrface/loot.frm"));

            auto dude = Game::Game::getInstance()->player();

            Helpers::CritterHelper critterHelper;
            Graphics::CritterAnimationFactory animationFactory;

            auto dudeCritter = animationFactory.buildStandingAnimation(
                critterHelper.armorFID(dude.get()),
                critterHelper.weaponId(dude.get()),
                Game::Orientation::SC
            );
            dudeCritter->setPosition({56, 47});
            addUI(dudeCritter.release());

            // FIXME: chests and lockers should be shown opened and centered vertically
            auto objectCopy = new Game::Object();
            objectCopy->setFID(object()->FID());
            objectCopy->ui()->setPosition({432, 38});
            addUI(objectCopy->ui());

            addUI("button_done", _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {478, 331}));
            getUI("button_done")->mouseClickHandler().add(std::bind(&Container::onDoneButtonClick, this, std::placeholders::_1));

            // TODO: disable buttons if there is nowhere to scroll
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

            auto dudeList = new UI::ItemsList({174, 35});
            dudeList->setItems(Game::Game::getInstance()->player()->inventory());
            addUI(dudeList);

            auto dudeListScrollUpButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_UP_ARROW, {127, 40});
            dudeListScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(dudeList); });
            addUI(dudeListScrollUpButton);

            auto dudeListScrollDownButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_DOWN_ARROW, {127, 66});
            dudeListScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(dudeList); });
            addUI(dudeListScrollDownButton);

            auto containerList = new UI::ItemsList({292, 35});
            containerList->setItems(object()->inventory());
            addUI(containerList);

            auto containerListScrollUpButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_UP_ARROW, {379, 40});
            containerListScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(containerList); });
            addUI(containerListScrollUpButton);

            auto containerListScrollDownButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_DOWN_ARROW, {379, 66});
            containerListScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(containerList); });
            addUI(containerListScrollDownButton);

            auto btnTakeAll = _imageButtonFactory->getByType(ImageButtonType::INVENTORY_TAKE_ALL, {432, 203});
            btnTakeAll->mouseClickHandler().add([dudeList, containerList](...) {

                for(const auto &i : *containerList->items()) {
                    dudeList->items()->push_back(i);
                }
                containerList->items()->clear();
                containerList->update();
                dudeList->update();
            });
            addUI(btnTakeAll);

            dudeList->itemDragStopHandler().add([containerList, dudeList](Event::Mouse* event){ containerList->onItemDragStop(event, dudeList); });
            containerList->itemDragStopHandler().add([dudeList, containerList](Event::Mouse* event){ dudeList->onItemDragStop(event, containerList); });
        }

        Game::ContainerItemObject* Container::object() const
        {
            return _object;
        }

        void Container::onDoneButtonClick(Event::Mouse*)
        {
            Game::Game::getInstance()->popState();
        }

        void Container::onStateActivate(Event::State* event)
        {
            _previousCursor = mouse()->cursor();
            mouse()->setCursor(Input::Mouse::Cursor::BIG_ARROW);
        }

        void Container::onStateDeactivate(Event::State* event) {
            mouse()->setCursor(_previousCursor);
        }

        void Container::onKeyDown(Event::Keyboard* event)
        {
            if (event->keyCode() == SDLK_ESCAPE) {
                Game::Game::getInstance()->popState();
            }
        }
    }
}
