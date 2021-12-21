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
        PlayerEditAge::PlayerEditAge(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        void PlayerEditAge::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(true);

            Point backgroundPos = Point((Game::Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();

            auto bg = resourceManager->getImage("art/intrface/charwin.frm");
            bg->setPosition(backgroundPos + Point(160, 0));

            auto ageBox = resourceManager->getImage("art/intrface/agebox.frm");
            ageBox->setPosition(backgroundPos + Point(168, 10));

            auto doneBox = resourceManager->getImage("art/intrface/donebox.frm");
            doneBox->setPosition(backgroundPos + Point(175, 40));

            auto decButton = imageButtonFactory->getByType(ImageButtonType::LEFT_ARROW, {backgroundX + 178, backgroundY + 14});
            decButton->mouseClickHandler().add(std::bind(&PlayerEditAge::onDecButtonClick, this, std::placeholders::_1));

            auto incButton = imageButtonFactory->getByType(ImageButtonType::RIGHT_ARROW, {backgroundX + 262, backgroundY + 14});
            incButton->mouseClickHandler().add(std::bind(&PlayerEditAge::onIncButtonClick, this, std::placeholders::_1));

            auto doneButton= imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 188, backgroundY + 43});
            doneButton->mouseClickHandler().add(std::bind(&PlayerEditAge::onDoneButtonClick, this, std::placeholders::_1));

            auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), backgroundX+210, backgroundY+43);

            doneLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            _counter = new UI::BigCounter({backgroundX + 215, backgroundY + 13});
            _counter->setNumber(Game::Game::getInstance()->player()->age());

            addUI(bg);
            addUI(ageBox);
            addUI(doneBox);
            addUI(incButton);
            addUI(decButton);
            addUI(doneLabel);
            addUI(doneButton);
            addUI(_counter);

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
            Game::Game::getInstance()->popState();
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
            Game::Game::getInstance()->player()->setAge(_counter->number());
            Game::Game::getInstance()->popState();
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
