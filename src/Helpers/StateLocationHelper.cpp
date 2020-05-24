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
        std::unique_ptr<State::Location> StateLocationHelper::getInitialLocationState() const
        {
            GameLocationHelper gameLocationHelper;
            std::unique_ptr<Game::Location> initialLocation = gameLocationHelper.getInitialLocation();

            auto game = Game::getInstance();

            auto locationState = std::make_unique<State::Location>(
                game->player(),
                game->mouse(),
                game->settings(),
                game->renderer(),
                game->mixer(),
                game->gameTime(),
                std::make_unique<UI::ResourceManager>()
            );

            locationState->setElevation(initialLocation->defaultElevationIndex());
            locationState->setLocation(std::move(initialLocation));
            return locationState;
        }
    }
}
