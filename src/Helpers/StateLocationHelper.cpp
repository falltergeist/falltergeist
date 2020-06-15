#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Helpers/GameLocationHelper.h"
#include "../Helpers/StateLocationHelper.h"
#include "../State/Location.h"
#include "../UI/ResourceManager.h"

namespace Falltergeist
{
    namespace Helpers
    {
        StateLocationHelper::StateLocationHelper(std::shared_ptr<ILogger> logger)
        {
            this->logger = std::move(logger);
        }

        State::Location* StateLocationHelper::getInitialLocationState() const
        {
            GameLocationHelper gameLocationHelper(logger);
            auto initialLocation = gameLocationHelper.getInitialLocation();

            auto game = Game::Game::getInstance();

            auto locationState = new State::Location(
                game->player(),
                game->mouse(),
                game->settings(),
                game->renderer(),
                game->mixer(),
                game->gameTime(),
                std::make_shared<UI::ResourceManager>(),
                logger
            );
            locationState->setElevation(initialLocation->defaultElevationIndex());
            locationState->setLocation(initialLocation);
            return locationState;
        }
    }
}
