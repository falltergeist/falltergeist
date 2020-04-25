#include "../State/PlayerCreateOptions.h"
#include "../Audio/Mixer.h"
#include "../functions.h"
#include "../Game/Game.h"
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

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        PlayerCreateOptions::PlayerCreateOptions(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        void PlayerCreateOptions::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(false);

            auto& background = *addUI(resourceManager->getImage("art/intrface/opbase.frm"));
            Point bgPos = Point((Game::getInstance()->renderer()->size() - background.size()) / 2);
            background.setPosition(bgPos);

            {
                auto saveButton = imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, bgPos.add(14, 18));
                saveButton->mouseClickHandler().add(   std::bind(&PlayerCreateOptions::onSaveButtonClick, this, std::placeholders::_1));
                addUI(std::move(saveButton));
            }

            {
                auto loadButton = imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, bgPos.add(14, 18 + 37));
                loadButton->mouseClickHandler().add(   std::bind(&PlayerCreateOptions::onLoadButtonClick, this, std::placeholders::_1));
                addUI(std::move(loadButton));
            }

            {
                auto printToFileButton = imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, bgPos.add(14, 18 + 37 * 2));
                printToFileButton->mouseClickHandler().add(std::bind(&PlayerCreateOptions::onPrintToFileButtonClick, this, std::placeholders::_1));
                addUI(std::move(printToFileButton));
            }

            {
                auto eraseButton = imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, bgPos.add(14, 18 + 37 * 3));
                eraseButton->mouseClickHandler().add(      std::bind(&PlayerCreateOptions::onEraseButtonClick, this, std::placeholders::_1));
                addUI(std::move(eraseButton));
            }

            {
                auto doneButton = imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, bgPos.add(14, 18 + 37 * 4));
                doneButton->mouseClickHandler().add(       std::bind(&PlayerCreateOptions::onDoneButtonClick, this, std::placeholders::_1));
                addUI(std::move(doneButton));
            }

            auto font = ResourceManager::getInstance()->font("font3.aaf");
            SDL_Color color = {0xb8, 0x9c, 0x28, 0xff};

            // label: save
            {
                auto saveButtonLabel = makeUI<UI::TextArea>(_t(MSG_EDITOR, 600), bgPos.add(8, 26));
                saveButtonLabel->setFont(font, color);
                saveButtonLabel->setWidth(150);
                saveButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            }

            // label: load
            {
                auto loadButtonLabel = makeUI<UI::TextArea>(_t(MSG_EDITOR, 601), bgPos.add(8, 26 + 37));
                loadButtonLabel->setFont(font, color);
                loadButtonLabel->setWidth(150);
                loadButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            }

            // label: print to file
            {
                auto printToFileButtonLabel = makeUI<UI::TextArea>(_t(MSG_EDITOR, 602), bgPos.add(8, 26 + 37 * 2));
                printToFileButtonLabel->setFont(font, color);
                printToFileButtonLabel->setWidth(150);
                printToFileButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            }

            // label: erase
            {
                auto eraseButtonLabel = makeUI<UI::TextArea>(_t(MSG_EDITOR, 603), bgPos.add(8, 26 + 37 * 3));
                eraseButtonLabel->setFont(font, color);
                eraseButtonLabel->setWidth(150);
                eraseButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            }

            // label: done
            {
                auto doneButtonLabel = makeUI<UI::TextArea>(_t(MSG_EDITOR, 604), bgPos.add(8, 26 + 37 * 4));
                doneButtonLabel->setFont(font, color);
                doneButtonLabel->setWidth(150);
                doneButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            }
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
            Game::getInstance()->popState();
        }

        void PlayerCreateOptions::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_RETURN:
                case SDLK_d:
                    Game::getInstance()->popState();
                    break;
            }
        }
    }
}
