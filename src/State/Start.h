#pragma once

#include "../Game/Timer.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace State
    {
        class Start final : public State
        {
            public:
                Start(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~Start() = default;

                void think(const float &deltaTime) override;
                void init() override;

            private:
                std::unique_ptr<Game::Timer> _delayTimer;
                std::shared_ptr<UI::IResourceManager> resourceManager;
        };
    }
}
