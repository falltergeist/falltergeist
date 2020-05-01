#pragma once

#include "../Game/MiscObject.h"

namespace Falltergeist
{
    namespace Game
    {
        class ExitMiscObject : public MiscObject
        {
            public:
                ExitMiscObject();
                ~ExitMiscObject() = default;

                int exitHexagonNumber() const;
                void setExitHexagonNumber(int value);

                int exitElevationNumber() const;
                void setExitElevationNumber(int value);

                int exitDirection() const;
                void setExitDirection(int value);

                int exitMapNumber() const;
                void setExitMapNumber(int value);

            protected:
                int _exitHexagonNumber = 0;
                int _exitElevationNumber = 0;
                int _exitDirection = 0;
                int _exitMapNumber = 0;
        };
    }
}
