// Project includes
#include "../State/Start.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/StatCollection.h"
#include "../Game/TraitCollection.h"
#include "../Graphics/Renderer.h"
#include "../Helpers/StateLocationHelper.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/CritterDialog.h"
#include "../State/Location.h"
#include "../State/MainMenu.h"
#include "../State/Movie.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib
#include <string>
#include <vector>
#include <memory>

namespace Falltergeist
{
    namespace State
    {
        using Helpers::StateLocationHelper;
        using Point = Graphics::Point;

        Start::Start(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<ILogger> logger
        ) : State(), _logger(logger), _resourceManager(resourceManager) {
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
                game->setState(new MainMenu(_resourceManager, _logger));
                game->pushState(new Movie(17));
                game->pushState(new Movie(1));
                game->pushState(new Movie(0));
            });

            Game::Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::WAIT);
        }

        void Start::think(const float &deltaTime)
        {
            _delayTimer->think(deltaTime);

            auto game = Game::Game::getInstance();
            State::think(deltaTime);
            if (game->settings()->forceLocation()) {
                auto combatTraitCollection = std::make_shared<Game::TraitCollection>();
                auto combatStatCollection = std::make_shared<Game::StatCollection>(combatTraitCollection);
                auto player = std::make_unique<Game::DudeObject>(combatStatCollection, combatTraitCollection);
                player->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
                game->setPlayer(std::move(player));

                StateLocationHelper stateLocationHelper(_logger);
                game->setState(stateLocationHelper.getInitialLocationState());
                return;
            }
        }
    }
}
