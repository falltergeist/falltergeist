#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace State
    {
        class GameMenu final : public State
        {
            public:
                GameMenu(std::shared_ptr<UI::IResourceManager> resourceManager);
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
                std::shared_ptr<UI::IResourceManager> resourceManager;
        };
    }
}
