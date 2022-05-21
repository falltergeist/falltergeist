#include <sstream>
#include "../State/SaveGame.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/State.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/ImageList.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        SaveGame::SaveGame(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse
        ) : State(mouse), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void SaveGame::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            auto game = Game::Game::getInstance();
            //auto player = Game::getInstance()->player();

            // background
            auto bg = _resourceManager->getImage("art/intrface/lsgame.frm");
            Point bgPos = Point((game->renderer()->size() - bg->size()) / 2);
            int bgX = bgPos.x();
            int bgY = bgPos.y();
            bg->setPosition(bgPos);
            addUI(bg);

            // BUTTONS

            // button: up arrow
            addUI("button_up", _imageButtonFactory->getByType(ImageButtonType::SMALL_UP_ARROW, {bgX + 35, bgY + 58}));
            // button: down arrow
            addUI("button_down", _imageButtonFactory->getByType(ImageButtonType::SMALL_DOWN_ARROW, {bgX + 35, bgY + 72}));

            // button: Done
            auto doneButton = _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {bgX + 391, bgY + 349});
            doneButton->mouseClickHandler().add(std::bind(&SaveGame::onDoneButtonClick, this, std::placeholders::_1));
            addUI(doneButton);

            // button: Cancel
            auto cancelButton = _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {bgX + 495, bgY + 349});
            cancelButton->mouseClickHandler().add(std::bind(&SaveGame::onCancelButtonClick, this, std::placeholders::_1));
            addUI(cancelButton);

            // LABELS
            std::string font3_907824ff = "font3.aaf";
            Graphics::Color color = {0x90, 0x78, 0x24, 0xff};

            // SAVE GAME LABEL
            auto saveGameLabel = new UI::TextArea(_t(MSG_LOAD_SAVE, 109), bgX+48, bgY+27);
            saveGameLabel->setFont(font3_907824ff, color);
            addUI(saveGameLabel);

            // DONE BUTTON LABEL
            auto doneButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 300), bgX+410, bgY+348);
            doneButtonLabel->setFont(font3_907824ff, color);
            addUI(doneButtonLabel);

            // CANCEL BUTTON LABEL
            auto cancelButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 121), bgX+515, bgY+348);
            cancelButtonLabel->setFont(font3_907824ff, color);
            addUI(cancelButtonLabel);
        }

        void SaveGame::onDoneButtonClick(Event::Mouse* event)
        {
            Game::Game::getInstance()->popState();
        }

        void SaveGame::onCancelButtonClick(Event::Mouse* event)
        {
            Game::Game::getInstance()->popState();
        }

        void SaveGame::onStateActivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void SaveGame::onStateDeactivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->popState();
        }

        void SaveGame::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    Game::Game::getInstance()->popState();
                    break;
            }
        }
    }
}
