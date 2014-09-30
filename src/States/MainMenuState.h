/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef FALLTERGEIST_MAINMENUSTATE_H
#define FALLTERGEIST_MAINMENUSTATE_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{
    
class MainMenuState : public State
{
public:
    MainMenuState();
    virtual ~MainMenuState();
    virtual void init();

    void onExitButtonClick(std::shared_ptr<MouseEvent> event);
    void onNewGameButtonClick(std::shared_ptr<MouseEvent> event);
    void onLoadGameButtonClick(std::shared_ptr<MouseEvent> event);
    void onSettingsButtonClick(std::shared_ptr<MouseEvent> event);
};

}
#endif // FALLTERGEIST_MAINMENUSTATE_H
