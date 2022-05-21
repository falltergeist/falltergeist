#include <string>
#include <vector>
#include <memory>
#include "../State/Start.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Helpers/StateLocationHelper.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/CritterDialog.h"
#include "../State/Location.h"
#include "../State/MainMenu.h"
#include "../State/Intro.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        using Helpers::StateLocationHelper;
        using Point = Graphics::Point;
        using Cursor = Input::Mouse::Cursor;

        Start::Start(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            std::shared_ptr<ILogger> logger
        ) : State(mouse), _logger(logger), _resourceManager(resourceManager) {
        }

        void Start::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            std::vector<std::string> splashes = {"splash0.rix", "splash1.rix", "splash2.rix", "splash3.rix", "splash4.rix", "splash5.rix", "splash6.rix"};

            auto renderer = Game::Game::getInstance()->renderer();

            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("splash", _resourceManager->getImage("art/splash/" + splashes.at(rand() % splashes.size())));

            auto game = Game::Game::getInstance();
            _delayTimer = std::make_unique<Game::Timer>(3000);
            _delayTimer->start();
            _delayTimer->tickHandler().add([game, this](Event::Event*) {
                game->setState(new Intro(_resourceManager, mouse(), _logger));
            });

        }

        void Start::think(const float &deltaTime)
        {
            _delayTimer->think(deltaTime);

            auto game = Game::Game::getInstance();
            State::think(deltaTime);
            if (game->settings()->forceLocation()) {
                auto player = std::make_unique<Game::DudeObject>();
                player->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
                game->setPlayer(std::move(player));

                StateLocationHelper stateLocationHelper(_logger);
                game->setState(stateLocationHelper.getInitialLocationState());
                return;
            }
        }

        void Start::onStateActivate(Event::State* event) {
            mouse()->setCursor(Cursor::WAIT);
        }
    }
}
