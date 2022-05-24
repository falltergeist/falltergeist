#include "../State/GameMenu.h"
#include "../Audio/Mixer.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/LoadGame.h"
#include "../State/Location.h"
#include "../State/SaveGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/PlayerPanel.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        GameMenu::GameMenu(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            std::shared_ptr<ILogger> logger
        ) : State(mouse), _logger(logger), _resourceManager(resourceManager)
        {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void GameMenu::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(false);

            auto background = _resourceManager->getImage("art/intrface/opbase.frm");
            auto panelHeight = Game::Game::getInstance()->locationState()->playerPanel()->size().height();

            auto backgroundPos = (Game::Game::getInstance()->renderer()->size() - background->size() - Point(0, panelHeight)) / 2;
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();

            auto saveGameButton    = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18});
            auto loadGameButton    = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37});
            auto preferencesButton = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37 * 2});
            auto exitGameButton    = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37 * 3});
            auto doneButton        = _imageButtonFactory->getByType(ImageButtonType::OPTIONS_BUTTON, {backgroundX + 14, backgroundY + 18 + 37 * 4});

            preferencesButton->mouseClickHandler().add([this](Event::Event* event){ this->doPreferences(); });
            exitGameButton->mouseClickHandler().add(   [this](Event::Event* event){ this->doExit(); });
            doneButton->mouseClickHandler().add(       [this](Event::Event* event){ this->closeMenu(); });

            auto font = ResourceManager::getInstance()->font("font3.aaf");
            Graphics::Color color = {0xb8, 0x9c, 0x28, 0xff};

            // label: save game
            auto saveGameButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 0), backgroundX+8, backgroundY+26);
            saveGameButtonLabel->setFont(font, color);
            saveGameButtonLabel->setSize({150, 0});
            saveGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            saveGameButton->mouseClickHandler().add([this](Event::Event* event){ this->doSaveGame(); });

            // label: load game
            auto loadGameButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 1), backgroundX+8, backgroundY+26+37);
            loadGameButtonLabel->setFont(font, color);
            loadGameButtonLabel->setSize({150, 0});
            loadGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            loadGameButton->mouseClickHandler().add([this](Event::Event* event){ this->doLoadGame(); });

            // label: preferences
            auto preferencesButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 2), backgroundX+8, backgroundY+26+37*2);
            preferencesButtonLabel->setFont(font, color);
            preferencesButtonLabel->setSize({150, 0});
            preferencesButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: exit game
            auto exitGameButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 3), backgroundX+8, backgroundY+26+37*3);
            exitGameButtonLabel->setFont(font, color);
            exitGameButtonLabel->setSize({150, 0});
            exitGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: done
            auto doneButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 4), backgroundX+8, backgroundY+26+37*4);
            doneButtonLabel->setFont(font, color);
            doneButtonLabel->setSize({150, 0});
            doneButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            background->setPosition(backgroundPos);

            addUI(background);
            addUI(saveGameButton);
            addUI(loadGameButton);
            addUI(preferencesButton);
            addUI(exitGameButton);
            addUI(doneButton);
            addUI(saveGameButtonLabel);
            addUI(loadGameButtonLabel);
            addUI(preferencesButtonLabel);
            addUI(exitGameButtonLabel);
            addUI(doneButtonLabel);
        }

        void GameMenu::doSaveGame()
        {
            Game::Game::getInstance()->pushState(new SaveGame(_resourceManager, mouse()));
        }

        void GameMenu::doLoadGame()
        {
            Game::Game::getInstance()->pushState(new LoadGame(_resourceManager, mouse()));
        }

        void GameMenu::doPreferences()
        {
            Game::Game::getInstance()->pushState(new SettingsMenu(_resourceManager, mouse()));
        }

        void GameMenu::doExit()
        {
            Game::Game::getInstance()->pushState(new ExitConfirm(_resourceManager, mouse(), _logger));
        }

        void GameMenu::closeMenu()
        {
            Game::Game::getInstance()->popState();
        }

        void GameMenu::onStateActivate(Event::State* event) {
            _previousCursor = mouse()->cursor();
            mouse()->setCursor(Input::Mouse::Cursor::BIG_ARROW);
        }

        void GameMenu::onStateDeactivate(Event::State* event) {
            mouse()->setCursor(_previousCursor);
        }

        void GameMenu::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_d:
                    closeMenu();
                    break;
                case SDLK_s:
                    doSaveGame();
                    break;
                case SDLK_l:
                    doLoadGame();
                    break;
                case SDLK_p:
                    doPreferences();
                    break;
                case SDLK_e:
                    doExit();
                    break;
            }
        }
    }
}
