#pragma once

// Project includes
#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

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
        class GameMenu final : public State
        {
            public:
                GameMenu(std::shared_ptr<UI::IResourceManager> resourceManager, std::shared_ptr<ILogger> logger);
                virtual ~GameMenu() = default;

                void init() override;

                void doSaveGame();
                void doLoadGame();
                void doPreferences();
                void doExit();
                void closeMenu();

                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;

            private:
                std::shared_ptr<ILogger> logger;
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
