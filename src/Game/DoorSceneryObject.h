#pragma once

// Project includes
#include "../Game/IClosable.h"
#include "../Game/ILockable.h"
#include "../Game/SceneryObject.h"
#include "../ILogger.h"

// Third-party includes

// stdlib

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
        class DoorSceneryObject : public SceneryObject, public IClosable, public ILockable {
            public:
                DoorSceneryObject(std::shared_ptr<ILogger> logger);
                ~DoorSceneryObject() = default;

                bool closed() const override;
                void close() override;
                void open() override;

                bool locked() const override;
                void lock() override;
                void unlock() override;

                bool canWalkThru() const override;

                void use_p_proc(CritterObject* usedBy) override;

                void onOpeningAnimationEnded(std::shared_ptr<UI::AnimationQueue> target);

                void onClosingAnimationEnded(std::shared_ptr<UI::AnimationQueue> target);

            private:
                std::shared_ptr<ILogger> logger;
                bool _closed = true;
                bool _locked = false;
        };
    }
}
