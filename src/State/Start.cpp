#include <ctime>
#include <string>
#include <vector>
#include <memory>
#include "../State/Start.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Helpers/StateLocationHelper.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/CritterDialog.h"
#include "../State/Location.h"
#include "../State/MainMenu.h"
#include "../State/Movie.h"
#include "../State/SettingsMenu.h"
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
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);

            std::vector<std::string> splashes = {"splash0.rix", "splash1.rix", "splash2.rix", "splash3.rix", "splash4.rix", "splash5.rix", "splash6.rix"};

            auto renderer = Game::getInstance()->renderer();

            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("splash", new UI::Image("art/splash/" + splashes.at(rand() % splashes.size())));

            _splashTicks = SDL_GetTicks();

            Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::WAIT);
        }

        void Start::think()
        {
            auto game = Game::getInstance();
            State::think();
            if (game->settings()->forceLocation())
            {
                auto player = std::make_unique<Game::DudeObject>();
                player->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
                game->setPlayer(std::move(player));

                StateLocationHelper stateLocationHelper;
                game->setState(stateLocationHelper.getInitialLocationState());
                return;
            }
            if (_splashTicks + 3000 < SDL_GetTicks())
            {
                game->setState(new MainMenu());
                game->pushState(new Movie(17));
                game->pushState(new Movie(1));
                game->pushState(new Movie(0));
            }
        }
    }
}
