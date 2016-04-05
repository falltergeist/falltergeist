/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_STATE_MAINMENU_H
#define FALLTERGEIST_STATE_MAINMENU_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../State/State.h"

// Third party includes

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

                void onStateActivate(Event::State* event);

                void onExitStart(Event::State* event);
                void onNewGameStart(Event::State* event);
                void onLoadGameStart(Event::State* event);
                void onIntroStart(Event::State* event);
                void onCreditsStart(Event::State* event);
        };
    }
}
#endif // FALLTERGEIST_STATE_MAINMENU_H
