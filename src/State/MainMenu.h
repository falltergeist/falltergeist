#pragma once

#include <memory>
#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }

    namespace State
    {
        class MainMenu final : public State
        {
            public:
                MainMenu(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    std::shared_ptr<ILogger> logger
                );

                ~MainMenu() override;

                void init() override;

                void onKeyDown(Event::Keyboard* event) override;

                void onStateActivate(Event::State* event) override;

                // TODO get rid of these 6 methods
                void onExitStart(Event::State* event);

                void onNewGameStart(Event::State* event);

                void onLoadGameStart(Event::State* event);

                void onIntroStart(Event::State* event);

                void onCreditsStart(Event::State* event);

            private:
                void _doIntro();

                void _doNewGame();

                void _doLoadGame();

                void _doSettings();

                void _doCredits();

                void _doExit();

                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
