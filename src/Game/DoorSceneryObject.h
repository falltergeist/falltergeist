#pragma once

#include "../Game/SceneryObject.h"

namespace Falltergeist
{
    namespace Event
    {
        class Event;
    }

    namespace Game
    {
        /**
         * Doors. Can be opened, closed, locked and unlocked.
         */
        class DoorSceneryObject : public SceneryObject
        {
            public:
                DoorSceneryObject();
                ~DoorSceneryObject() override = default;

                bool canWalkThru() const override;

                void use_p_proc(CritterObject* usedBy) override;

                void onOpeningAnimationEnded(Event::Event* event);
                void onClosingAnimationEnded(Event::Event* event);

            private:
                bool opened() const;
                void setOpened(bool value);
        };
    }
}
