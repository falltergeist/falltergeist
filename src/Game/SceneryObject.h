#pragma once

// Project includes
#include "../Game/Object.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Stationary object used as scenery.
         */
        class SceneryObject : public Object
        {
            public:
                enum class Subtype
                {
                    DOOR = 0,
                    STAIRS,
                    ELEVATOR,
                    LADDER,
                    GENERIC
                };

                SceneryObject();
                ~SceneryObject() = default;

                char soundId() const;
                void setSoundId(char soundId);

            protected:
                char _soundId = 0;
                Subtype _subtype;
        };
    }
}
