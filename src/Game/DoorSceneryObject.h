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

                bool opened() const;
                void setOpened(bool value);

                bool locked() const;
                void setLocked(bool value);

                bool canWalkThru() const override;

                void use_p_proc(CritterObject* usedBy) override;

                void onOpeningAnimationEnded(Event::Event* event);
                void onClosingAnimationEnded(Event::Event* event);

            protected:
                bool _opened = false;
                bool _locked = false;
        };
    }
}
