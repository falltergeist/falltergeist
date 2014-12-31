/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_MainMenu_H
#define FALLTERGEIST_MainMenu_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class MainMenu : public State
{
public:
    MainMenu();
    virtual ~MainMenu();
    virtual void init();

    void onExitButtonClick(MouseEvent* event);
    void onNewGameButtonClick(MouseEvent* event);
    void onLoadGameButtonClick(MouseEvent* event);
    void onSettingsButtonClick(MouseEvent* event);
    void onIntroButtonClick(MouseEvent* event);
    void onCreditsButtonClick(MouseEvent* event);

    void onStateActivate(StateEvent* event);

    void onExitStart(StateEvent* event);
    void onNewGameStart(StateEvent* event);
    void onLoadGameStart(StateEvent* event);
    void onIntroStart(StateEvent* event);
    void onCreditsStart(StateEvent* event);
};

}
}

#endif // FALLTERGEIST_MainMenu_H
