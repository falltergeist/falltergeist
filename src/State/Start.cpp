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
#include "../State/Movie.h"
#include "../UI/Image.h"

namespace Falltergeist
{
    using Helpers::StateLocationHelper;

    namespace State
    {
        Start::Start() : State()
        {
        }

        Start::~Start()
        {
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

            auto renderer = Game::getInstance()->renderer();

            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("splash", new UI::Image("art/splash/" + splashes.at(rand() % splashes.size())));

            _delayTimer = std::make_unique<Game::CountdownTimer>(3);

            Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::WAIT);
        }

        void Start::think(float deltaTime)
        {
            _delayTimer->think(deltaTime);

            auto game = Game::getInstance();
            State::think(deltaTime);
            if (game->settings()->forceLocation()) {
                auto player = std::make_unique<Game::DudeObject>();
                player->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
                game->setPlayer(std::move(player));

                StateLocationHelper stateLocationHelper;
                game->setState(stateLocationHelper.getInitialLocationState());
                return;
            }

            if (_delayTimer->isFinished()) {
                game->setState(new MainMenu());
                game->pushState(new Movie(17));
                game->pushState(new Movie(1));
                game->pushState(new Movie(0));
            }
        }
    }
}
