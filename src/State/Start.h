#pragma once

#include "../Game/Timer.h"
#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace State
    {
        class Start final : public State
        {
            public:
                Start(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    std::shared_ptr<ILogger> logger
                );

                virtual ~Start() = default;

                void think(const float &deltaTime) override;

                void init() override;

                void onStateActivate(Event::State* event) override;

            private:
                void _onSplashScreenDelayEnded();

                void _onFirstMovieEnded();

                std::shared_ptr<ILogger> _logger;

                std::unique_ptr<Game::Timer> _delayTimer;

                std::shared_ptr<UI::IResourceManager> _resourceManager;
        };
    }
}
