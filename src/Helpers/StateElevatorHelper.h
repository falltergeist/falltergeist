#pragma once

#include <memory>
#include <string>
#include "../ILogger.h"
#include "../Game/Elevator.h"

namespace Falltergeist
{
    namespace Game
    {
        class Elevator;
    }
    namespace Helpers
    {
        class StateElevatorHelper
        {
            public:
                StateElevatorHelper(std::shared_ptr<ILogger> logger);
                Game::Elevator* getByType(uint32_t type);

            private:
                std::shared_ptr<ILogger> logger;
                std::vector<Game::Elevator*> _elevators;
        };
    }
}
