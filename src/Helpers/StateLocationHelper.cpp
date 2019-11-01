#include "../Game/Location.h"
#include "../Helpers/GameLocationHelper.h"
#include "../Helpers/StateLocationHelper.h"
#include "../State/Location.h"

namespace Falltergeist
{
    namespace Helpers
    {
        State::Location* StateLocationHelper::getInitialLocationState() const
        {
            GameLocationHelper gameLocationHelper;
            auto initialLocation = gameLocationHelper.getInitialLocation();

            auto locationState = new State::Location();
            locationState->setElevation(initialLocation->defaultElevationIndex());
            locationState->setLocation(initialLocation);
            return locationState;
        }
    }
}
