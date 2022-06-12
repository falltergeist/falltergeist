// Project includes
#include "../State/PlayerCreateOptions.h"
#include "../Audio/Mixer.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/LoadGame.h"
#include "../State/Location.h"
#include "../State/SaveGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        PlayerCreateOptions::PlayerCreateOptions(
            std::shared_ptr<UI::IResourceManager> resourceManager
        ) : State(), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void PlayerCreateOptions::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(false);

            auto background = _resourceManager->getImage("art/intrface/opbase.frm");

            Point backgroundPos = Point((Game::Game::getInstance()->renderer()->size() - background->size()) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();

            auto saveButton = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18});
            auto loadButton = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37});
            auto printToFileButton = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37 * 2});
            auto eraseButton = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37 * 3});
            auto doneButton = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37 * 4});

            saveButton->mouseClickHandler().add(   std::bind(&PlayerCreateOptions::onSaveButtonClick, this, std::placeholders::_1));
            loadButton->mouseClickHandler().add(   std::bind(&PlayerCreateOptions::onLoadButtonClick, this, std::placeholders::_1));
            printToFileButton->mouseClickHandler().add(std::bind(&PlayerCreateOptions::onPrintToFileButtonClick, this, std::placeholders::_1));
            eraseButton->mouseClickHandler().add(      std::bind(&PlayerCreateOptions::onEraseButtonClick, this, std::placeholders::_1));
            doneButton->mouseClickHandler().add(       std::bind(&PlayerCreateOptions::onDoneButtonClick, this, std::placeholders::_1));

            auto font = ResourceManager::getInstance()->font("font3.aaf");
            Graphics::Color color = {0xb8, 0x9c, 0x28, 0xff};

            // label: save
            auto saveButtonLabel = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 600), backgroundX+8, backgroundY+26);
            saveButtonLabel->setFont(font, color);
            saveButtonLabel->setWidth(150);
            saveButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: load
            auto loadButtonLabel = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 601), backgroundX+8, backgroundY+26+37);
            loadButtonLabel->setFont(font, color);
            loadButtonLabel->setWidth(150);
            loadButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: print to file
            auto printToFileButtonLabel = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 602), backgroundX+8, backgroundY+26+37*2);
            printToFileButtonLabel->setFont(font, color);
            printToFileButtonLabel->setWidth(150);
            printToFileButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: erase
            auto eraseButtonLabel = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 603), backgroundX+8, backgroundY+26+37*3);
            eraseButtonLabel->setFont(font, color);
            eraseButtonLabel->setWidth(150);
            eraseButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: done
            auto doneButtonLabel = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 604), backgroundX+8, backgroundY+26+37*4);
            doneButtonLabel->setFont(font, color);
            doneButtonLabel->setWidth(150);
            doneButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            background->setPosition(backgroundPos);

            addUI(background);

            addUI(saveButton);
            addUI(loadButton);
            addUI(printToFileButton);
            addUI(eraseButton);
            addUI(doneButton);

            addUI(saveButtonLabel);
            addUI(loadButtonLabel);
            addUI(printToFileButtonLabel);
            addUI(eraseButtonLabel);
            addUI(doneButtonLabel);
        }

        void PlayerCreateOptions::onSaveButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new SavePlayerStatState());
        }

        void PlayerCreateOptions::onLoadButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new LoadPlayerStatState());
        }

        void PlayerCreateOptions::onPrintToFileButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new SettingsMenu());
        }

        void PlayerCreateOptions::onEraseButtonClick(Event::Mouse* event)
        {
        //    Game::getInstance()->pushState(new EraseConfirmState());
        }

        void PlayerCreateOptions::onDoneButtonClick(Event::Mouse* event)
        {
            Game::Game::getInstance()->popState();
        }

        void PlayerCreateOptions::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_RETURN:
                case SDLK_d:
                    Game::Game::getInstance()->popState();
                    break;
            }
        }
    }
}
