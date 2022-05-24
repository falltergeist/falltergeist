#include "../State/PlayerEditGender.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/ImageList.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        PlayerEditGender::PlayerEditGender(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse
        ) : State(mouse), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void PlayerEditGender::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(true);

            Point bgPos = Point((Game::Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
            int bgX = bgPos.x();
            int bgY = bgPos.y();

            auto bg = _resourceManager->getImage("art/intrface/charwin.frm");
            bg->setPosition(bgPos + Point(236, 0));

            _maleImage = new UI::ImageList({bgX + 260, bgY +2}, {
                _resourceManager->getImage("art/intrface/maleoff.frm"),
                _resourceManager->getImage("art/intrface/maleon.frm")
            });
            _maleImage->mouseClickHandler().add(std::bind(&PlayerEditGender::onMaleButtonPress, this, std::placeholders::_1));

            _femaleImage = new UI::ImageList({bgX + 310, bgY + 2}, {
                _resourceManager->getImage("art/intrface/femoff.frm"),
                _resourceManager->getImage("art/intrface/femon.frm")
            });
            _femaleImage->mouseClickHandler().add(std::bind(&PlayerEditGender::onFemaleButtonPress, this, std::placeholders::_1));

            auto doneBox = _resourceManager->getImage("art/intrface/donebox.frm");
            doneBox->setPosition(bgPos + Point(250, 42));

            auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX+281, bgY+45);
            doneLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            auto doneButton = _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {bgX + 260, bgY + 45});
            doneButton->mouseClickHandler().add(std::bind(&PlayerEditGender::onDoneButtonClick, this, std::placeholders::_1));

            addUI(bg);
            addUI(doneBox);
            addUI(doneButton);
            addUI(doneLabel);
            addUI(_maleImage);
            addUI(_femaleImage);
            setGender(Game::Game::getInstance()->player()->gender());
        }

        void PlayerEditGender::onDoneButtonClick(Event::Mouse* event)
        {
            Game::Game::getInstance()->player()->setGender(_gender);
            Game::Game::getInstance()->popState();
        }

        void PlayerEditGender::onFemaleButtonPress(Event::Mouse* event)
        {
            setGender(GENDER::FEMALE);
        }

        void PlayerEditGender::onMaleButtonPress(Event::Mouse* event)
        {
            setGender(GENDER::MALE);
        }

        void PlayerEditGender::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    Game::Game::getInstance()->popState();
                    break;
                case SDLK_RETURN:
                    Game::Game::getInstance()->player()->setGender(_gender);
                    Game::Game::getInstance()->popState();
                    break;
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    setGender(_gender);
                    break;
            }
        }

        void PlayerEditGender::setGender(GENDER gender)
        {
            _gender = gender;
            _maleImage->setCurrentImage(gender == GENDER::MALE ? 1 : 0);
            _femaleImage->setCurrentImage(gender == GENDER::FEMALE ? 1 : 0);
        }
    }
}
