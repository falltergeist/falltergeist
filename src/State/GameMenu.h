#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class GameMenu : public State
        {
            public:
                GameMenu();
                ~GameMenu() override;

                void init() override;

                void doSaveGame();
                void doLoadGame();
                void doPreferences();
                void doExit();
                void closeMenu();

                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
        };
    }
}
