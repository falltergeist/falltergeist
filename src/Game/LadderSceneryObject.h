#pragma once

// Project includes
#include "../Game/SceneryObject.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        class LadderSceneryObject : public SceneryObject
        {
            public:
                LadderSceneryObject();
                ~LadderSceneryObject() = default;
                void use_p_proc(CritterObject* usedBy) override;

                int exitHexagonNumber() const;
                void setExitHexagonNumber(int value);

                int exitElevationNumber() const;
                void setExitElevationNumber(int value);

                int exitMapNumber() const;
                void setExitMapNumber(int value);

            protected:
                int _exitHexagonNumber = 0;
                int _exitElevationNumber = 0;
                int _exitMapNumber = 0;
        };
    }
}
