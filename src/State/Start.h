#pragma once

// Project includes
#include "../Game/Timer.h"
#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace State
    {
        class Start final : public State
        {
            public:
                Start(std::shared_ptr<UI::IResourceManager> resourceManager, std::shared_ptr<ILogger> logger);
                virtual ~Start() = default;

                void think(const float &deltaTime) override;
                void init() override;

            private:
                std::shared_ptr<ILogger> logger;
                std::unique_ptr<Game::Timer> _delayTimer;
                std::shared_ptr<UI::IResourceManager> resourceManager;
        };
    }
}
