#include "../State/PlayerEditAlert.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        PlayerEditAlert::PlayerEditAlert(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        void PlayerEditAlert::setMessage(const std::string& message)
        {
            _message = message;
        }

        void PlayerEditAlert::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(true);

            auto bg = resourceManager->getImage("art/intrface/lgdialog.frm");

            Point bgPos = Point((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
            int bgX = bgPos.x();
            int bgY = bgPos.y();

            bg->setPosition(bgPos.add(164, 173));
            addUI(bg);

            {
                auto& message = *makeUI<UI::TextArea>(_message.c_str(), bgPos.add(194, 213));
                message.setWidth(250);
                message.setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
                message.setFont("font1.aaf", {0xff, 0x9f, 0x48, 0xff});
            }

            {
                auto& doneBox = *addUI(resourceManager->getImage("art/intrface/donebox.frm"));
                doneBox.setPosition(bgPos + Point(254, 270));
            }

            {
                auto& doneButton = *addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {bgX + 264, bgY + 273}));
                doneButton.mouseClickHandler().add([this](Event::Mouse* event) {
                                                        this->onDoneButtonClick(event);
                                                    });
            }

            {
                auto& doneLabel = *makeUI<UI::TextArea>(_t(MSG_EDITOR, 100), bgX + 284, bgY + 273);
                doneLabel.setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});
            }
        }

        void PlayerEditAlert::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }
    }
}
