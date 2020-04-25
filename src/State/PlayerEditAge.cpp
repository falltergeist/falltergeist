#include "../State/PlayerEditAge.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../UI/BigCounter.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        PlayerEditAge::PlayerEditAge(std::shared_ptr<UI::IResourceManager> _resourceManager) :
            State{},
            resourceManager(std::move(_resourceManager)),
            imageButtonFactory{std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager)}
        {
        }

        void PlayerEditAge::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(true);

            Point bgPos = Point((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);

            {
                auto& bg = *addUI(resourceManager->getImage("art/intrface/charwin.frm"));
                bg.setPosition(bgPos.add(160, 0));
            }

            {
                auto& ageBox = *addUI(resourceManager->getImage("art/intrface/agebox.frm"));
                ageBox.setPosition(bgPos.add(168, 10));
            }

            {
                auto& doneBox = *addUI(resourceManager->getImage("art/intrface/donebox.frm"));
                doneBox.setPosition(bgPos.add(175, 40));
            }

            {
                auto& decButton = *addUI(imageButtonFactory->getByType(ImageButtonType::LEFT_ARROW, bgPos.add(178, 14)));
                decButton.mouseClickHandler().add(std::bind(&PlayerEditAge::onDecButtonClick, this, std::placeholders::_1));
            }

            {
                auto& incButton = *addUI(imageButtonFactory->getByType(ImageButtonType::RIGHT_ARROW, bgPos.add(262, 14)));
                incButton.mouseClickHandler().add(std::bind(&PlayerEditAge::onIncButtonClick, this, std::placeholders::_1));
            }

            {
                auto& doneButton = *addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, bgPos.add(188, 43)));
                doneButton.mouseClickHandler().add(std::bind(&PlayerEditAge::onDoneButtonClick, this, std::placeholders::_1));
            }

            {
                auto& doneLabel = *makeUI<UI::TextArea>(_t(MSG_EDITOR, 100), bgPos.add(210, 43));
                doneLabel.setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});
            }

            _counter = makeUI<UI::BigCounter>(bgPos.add(215, 13));
            _counter->setNumber(Game::getInstance()->player()->age());
        }

        void PlayerEditAge::onDecButtonClick(Event::Mouse* event)
        {
            doDec();
        }

        void PlayerEditAge::onIncButtonClick(Event::Mouse* event)
        {
            doInc();
        }

        void PlayerEditAge::onDoneButtonClick(Event::Mouse* event)
        {
            doDone();
        }

        void PlayerEditAge::doBack()
        {
            Game::getInstance()->popState();
        }

        void PlayerEditAge::doDec()
        {
            unsigned char age = _counter->number();
            if (age > 16)
            {
                age--;
                _counter->setNumber(age);
            }
        }

        void PlayerEditAge::doDone()
        {
            Game::getInstance()->player()->setAge(_counter->number());
            Game::getInstance()->popState();
        }

        void PlayerEditAge::doInc()
        {
            unsigned char age = _counter->number();
            if (age < 35)
            {
                age++;
                _counter->setNumber(age);
            }
        }

        void PlayerEditAge::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_RIGHT:
                    doInc();
                    break;
                case SDLK_LEFT:
                    doDec();
                    break;
                case SDLK_ESCAPE:
                    doBack();
                    break;
                case SDLK_RETURN:
                    doDone();
                    break;
            }
        }
    }
}
