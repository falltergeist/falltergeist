#pragma once

#include "../Game/SceneryObject.h"

namespace Falltergeist
{
    namespace Game
    {
        class ElevatorSceneryObject : public SceneryObject
        {
            public:
                ElevatorSceneryObject();
                ~ElevatorSceneryObject() = default;

                int elevatorType();
                void setElevatorType(int type);

                int elevatorLevel();
                void setElevatorLevel(int level);

            protected:
                int _elevatorType = 0;
                int _elevatorLevel = 0;
        };
    }
}
