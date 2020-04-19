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
            auto initialLocation = gameLocationHelper.getInitialLocation();

            auto game = Game::getInstance();

            auto locationState = std::make_unique<State::Location>(
                game->player(),
                game->mouse(),
                game->settings(),
                game->renderer(),
                game->mixer(),
                game->gameTime(),
                std::make_shared<UI::ResourceManager>()
            );
            locationState->setElevation(initialLocation->defaultElevationIndex());
            locationState->setLocation(initialLocation);
            return locationState;
        }
    }
}
