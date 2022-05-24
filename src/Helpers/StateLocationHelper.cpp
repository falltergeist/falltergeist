// Project includes
#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Helpers/GameLocationHelper.h"
#include "../Helpers/StateLocationHelper.h"
#include "../State/Location.h"
#include "../UI/ResourceManager.h"
#include "../PathFinding/Hexagon.h"

// Third-party includes

// stdlib

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

        State::Location* StateLocationHelper::getCustomLocationState(const std::string& name, uint32_t elevation, uint32_t position) const
        {
            GameLocationHelper gameLocationHelper(logger);
            auto initialLocation = gameLocationHelper.getByName(name);
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
            locationState->setElevation(elevation);
            initialLocation->setDefaultPosition(position);
            locationState->setLocation(initialLocation);

            return locationState;
        }
    }
}
