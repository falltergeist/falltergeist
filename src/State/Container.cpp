#include "../State/Container.h"
#include "../ResourceManager.h"
#include "../Game/ContainerItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../UI/Animation.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ItemsList.h"

namespace Falltergeist
{
    namespace State
    {
        Container::Container() : State()
        {
        }

        Container::~Container()
        {
        }

        void Container::init()
        {
            if (_initialized) return;

            setModal(true);
            setFullscreen(false);

            auto game = Game::getInstance();

            setPosition((game->renderer()->size() - Point(537, 376)) / 2);

            addUI("background", new UI::Image("art/intrface/loot.frm"));

            auto dudeCritter = Game::getInstance()->player()->generateAnimation("aa", Game::Orientation::SC);
            dudeCritter->setPosition({56, 47});
            addUI(dudeCritter);

            // FIXME: chests and lockers should be shown opened and centered vertically
            auto objectCopy = new Game::Object();
            objectCopy->setFID(object()->FID());
            objectCopy->ui()->setPosition({432, 38});
            addUI(objectCopy->ui());

            addUI("button_done", new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, 478, 331));
            getUI("button_done")->mouseClickHandler().add(std::bind(&Container::onDoneButtonClick, this, std::placeholders::_1));

            // TODO: disable buttons if there is nowhere to scroll
            auto scrollUp = [](UI::ItemsList *list) { if (list->canScrollUp()) list->scrollUp(); };
            auto scrollDown = [](UI::ItemsList *list) { if (list->canScrollDown()) list->scrollDown(); };

            auto dudeList = new UI::ItemsList({174, 35});
            dudeList->setItems(Game::getInstance()->player()->inventory());
            addUI(dudeList);

            auto dudeListScrollUpButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_UP_ARROW, 127, 40);
            dudeListScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(dudeList); });
            addUI(dudeListScrollUpButton);

            auto dudeListScrollDownButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_DOWN_ARROW, 127, 66);
            dudeListScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(dudeList); });
            addUI(dudeListScrollDownButton);

            auto containerList = new UI::ItemsList({292, 35});
            containerList->setItems(object()->inventory());
            addUI(containerList);

            auto containerListScrollUpButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_UP_ARROW, 379, 40);
            containerListScrollUpButton->mouseClickHandler().add([=](...) { scrollUp(containerList); });
            addUI(containerListScrollUpButton);

            auto containerListScrollDownButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_DOWN_ARROW, 379, 66);
            containerListScrollDownButton->mouseClickHandler().add([=](...) { scrollDown(containerList); });
            addUI(containerListScrollDownButton);

            auto btnTakeAll = new UI::ImageButton(UI::ImageButton::Type::INVENTORY_TAKE_ALL, 432, 203);
            btnTakeAll->mouseClickHandler().add([dudeList, containerList](...) {

                for(const auto &i : *containerList->items()) {
                    dudeList->items()->push_back(i);
                }
                containerList->items()->clear();
                containerList->update();
                dudeList->update();
            });
            addUI(btnTakeAll);

            dudeList->itemDragStopHandler().add([containerList](Event::Mouse* event){ containerList->onItemDragStop(event); });
            containerList->itemDragStopHandler().add([dudeList](Event::Mouse* event){ dudeList->onItemDragStop(event); });

        }

        Game::ContainerItemObject* Container::object()
        {
            return _object;
        }

        void Container::setObject(Game::ContainerItemObject* object)
        {
            _object = object;
        }

        void Container::onDoneButtonClick(Event::Mouse*)
        {
            Game::getInstance()->popState();
        }

        void Container::onStateActivate(Event::State*)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void Container::onStateDeactivate(Event::State*)
        {
            Game::getInstance()->mouse()->popState();
        }

        void Container::onKeyDown(Event::Keyboard* event)
        {
            if (event->keyCode() == SDLK_ESCAPE)
            {
                Game::getInstance()->popState();
            }
        }
    }
}
