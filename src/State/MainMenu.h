#pragma once

#include <memory>
#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class MainMenu : public State
        {
            public:
                MainMenu();
                ~MainMenu() override;

                void init() override;

                void onExitButtonClick(Event::Mouse* event);
                void onNewGameButtonClick(Event::Mouse* event);
                void onLoadGameButtonClick(Event::Mouse* event);
                void onSettingsButtonClick(Event::Mouse* event);
                void onIntroButtonClick(Event::Mouse* event);
                void onCreditsButtonClick(Event::Mouse* event);
                void doExit();
                void doNewGame();
                void doLoadGame();
                void doSettings();
                void doIntro();
                void doCredits();
                void onKeyDown(Event::Keyboard* event) override;

                void onStateActivate(Event::State* event) override;

                void onExitStart(Event::State* event);
                void onNewGameStart(Event::State* event);
                void onLoadGameStart(Event::State* event);
                void onIntroStart(Event::State* event);
                void onCreditsStart(Event::State* event);
        };
    }
}
