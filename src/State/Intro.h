#pragma once

#include "../State/State.h"
#include "../ILogger.h"

namespace Falltergeist::State {
    class Intro final : public State {
    public:
        Intro(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            std::shared_ptr<ILogger> logger
        );

        void init() override;

    private:
        void _onFirstMovieEnded();

        void _onSecondMovieEnded();

        void _onThirdMovieEnded();

        std::shared_ptr<UI::IResourceManager> _resourceManager;

        std::shared_ptr<ILogger> _logger;
    };
}
