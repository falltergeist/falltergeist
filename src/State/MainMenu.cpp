#include <sstream>
#include "../State/MainMenu.h"
#include "../Audio/Mixer.h"
#include "../Event/State.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Credits.h"
#include "../State/Intro.h"
#include "../State/LoadGame.h"
#include "../State/NewGame.h"
#include "../State/SettingsMenu.h"
#include "../UI/Animation.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        MainMenu::MainMenu(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            std::shared_ptr<ILogger> logger
        ) : State(mouse), _logger(logger), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        MainMenu::~MainMenu()
        {
            Game::Game::getInstance()->mixer()->stopMusic();
        }

        void MainMenu::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            auto renderer = Game::Game::getInstance()->renderer();
            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("background", _resourceManager->getImage("art/intrface/mainmenu.frm"));

            // intro button
            auto introButton = addUI(_imageButtonFactory->getByType(ImageButtonType::MENU_RED_CIRCLE, {30, 19}));
            introButton->mouseClickHandler().add(std::bind(&MainMenu::_doIntro, this));

            // new game button
            auto newGameButton = addUI(_imageButtonFactory->getByType(ImageButtonType::MENU_RED_CIRCLE, {30, 19 + 41}));
            newGameButton->mouseClickHandler().add(std::bind(&MainMenu::_doNewGame, this));

            // load game button
            auto loadGameButton = addUI(_imageButtonFactory->getByType(ImageButtonType::MENU_RED_CIRCLE, {30, 19 + 41 * 2}));
            loadGameButton->mouseClickHandler().add(std::bind(&MainMenu::_doLoadGame, this));

            // settings button
            auto settingsButton = addUI(_imageButtonFactory->getByType(ImageButtonType::MENU_RED_CIRCLE, {30, 19 + 41 * 3}));
            settingsButton->mouseClickHandler().add(std::bind(&MainMenu::_doSettings, this));

            // credits button
            auto creditsButton = addUI(_imageButtonFactory->getByType(ImageButtonType::MENU_RED_CIRCLE, {30, 19 + 41 * 4}));
            creditsButton->mouseClickHandler().add(std::bind(&MainMenu::_doCredits, this));

            // exit button
            auto exitButton = addUI(_imageButtonFactory->getByType(ImageButtonType::MENU_RED_CIRCLE, {30, 19 + 41 * 5}));
            exitButton->mouseClickHandler().add(std::bind(&MainMenu::_doExit, this));

            auto font4 = ResourceManager::getInstance()->font("font4.aaf");
            Graphics::Color color = {0xb8, 0x9c, 0x28, 0xff};

            // "Intro" label
            auto introButtonLabel = new UI::TextArea("INTRO", 50, 20);
            introButtonLabel->setFont(font4, color);
            introButtonLabel->setWidth(150);
            introButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // "New Game" label
            auto newGameButtonLabel = new UI::TextArea("NEW GAME", 50, 20 + 41);
            newGameButtonLabel->setFont(font4, color);
            newGameButtonLabel->setWidth(150);
            newGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // "Load Game" label
            auto loadGameButtonLabel = new UI::TextArea("LOAD GAME", 50, 20 + 41*2);
            loadGameButtonLabel->setFont(font4, color);
            loadGameButtonLabel->setWidth(150);
            loadGameButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // "Options" label
            auto optionsButtonLabel = new UI::TextArea("OPTIONS", 50, 20 + 41*3);
            optionsButtonLabel->setFont(font4, color);
            optionsButtonLabel->setWidth(150);
            optionsButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // "Credits" label
            auto creditsButtonLabel = new UI::TextArea("CREDITS", 50, 20 + 41*4);
            creditsButtonLabel->setFont(font4, color);
            creditsButtonLabel->setWidth(150);
            creditsButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // "Exit" label
            auto exitButtonLabel = new UI::TextArea("EXIT", 50, 20 + 41*5);
            exitButtonLabel->setFont(font4, color);
            exitButtonLabel->setWidth(150);
            exitButtonLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // Text areas
            addUI(introButtonLabel);
            addUI(newGameButtonLabel);
            addUI(loadGameButtonLabel);
            addUI(optionsButtonLabel);
            addUI(creditsButtonLabel);
            addUI(exitButtonLabel);
        }

        void MainMenu::_doExit() {
            auto game = Game::Game::getInstance();
            fadeDoneHandler().clear();
            fadeDoneHandler().add([=](Event::Event* event){
                fadeDoneHandler().clear();
                game->mixer()->stopMusic();
                game->quit();
            });
            game->renderer()->fadeOut(0,0,0,1000);
        }

        void MainMenu::_doNewGame() {
            auto game = Game::Game::getInstance();
            fadeDoneHandler().clear();
            fadeDoneHandler().add([=](Event::Event* event){
                fadeDoneHandler().clear();
                game->pushState(new NewGame(_resourceManager, mouse(), _logger));
            });
            game->renderer()->fadeOut(0,0,0,1000);
        }

        void MainMenu::_doLoadGame() {
            auto game = Game::Game::getInstance();
            fadeDoneHandler().clear();
            fadeDoneHandler().add([=](Event::Event* event){
                fadeDoneHandler().clear();
                game->pushState(new LoadGame(_resourceManager, mouse()));
            });
            game->renderer()->fadeOut(0,0,0,1000);
        }

        void MainMenu::_doSettings() {
            Game::Game::getInstance()->pushState(new SettingsMenu(_resourceManager, mouse()));
        }

        void MainMenu::_doIntro() {
            auto game = Game::Game::getInstance();
            fadeDoneHandler().clear();
            fadeDoneHandler().add([=](Event::Event* event){
                fadeDoneHandler().clear();
                game->setState(new Intro(_resourceManager, mouse(), _logger));
            });
            game->renderer()->fadeOut(0,0,0,1000);
        }

        void MainMenu::_doCredits() {
            auto game = Game::Game::getInstance();
            fadeDoneHandler().clear();
            fadeDoneHandler().add([=](Event::Event* event){
                fadeDoneHandler().clear();
                game->pushState(new Credits(mouse()));
            });
            game->renderer()->fadeOut(0,0,0,1000);
        }

        void MainMenu::onKeyDown(Event::Keyboard* event) {
            switch (event->keyCode()) {
                case SDLK_e:
                case SDLK_ESCAPE:
                    _doExit();
                    break;
                case SDLK_n:
                    _doNewGame();
                    break;
                case SDLK_l:
                    _doLoadGame();
                    break;
                case SDLK_i:
                    _doIntro();
                    break;
                case SDLK_c:
                    _doCredits();
                    break;
                case SDLK_o:
                    _doSettings();
                    break;
            }
        }

        void MainMenu::onStateActivate(Event::State* event) {
            mouse()->setCursor(Input::Mouse::Cursor::BIG_ARROW);
            Game::Game::getInstance()->mixer()->playACMMusic("07desert.acm",true);
            Game::Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
        }
    }
}
