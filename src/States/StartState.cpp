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

// C++ standard includes
#include <vector>
#include <string>
#include <ctime>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../States/PlayerEditState.h"
#include "../States/SettingsMenuState.h"
#include "../States/CritterDialogState.h"
#include "../States/StartState.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

StartState::StartState() : State()
{
}

StartState::~StartState()
{
}

void StartState::init()
{
    State::init();
    
    std::vector<std::string> splashes = {"splash0.rix", "splash1.rix", "splash2.rix", "splash3.rix", "splash4.rix", "splash5.rix", "splash6.rix"};
    
    srand(time(NULL)); // seed
    auto splash = std::shared_ptr<Image>(new Image("art/splash/" + splashes.at(rand() % splashes.size())));
    add(splash);
    _splashTicks = SDL_GetTicks();

    Game::getInstance()->mouse()->setType(Mouse::WAIT);
}

void StartState::think()
{
    State::think();
    Game::getInstance()->setState(std::shared_ptr<LocationState>(new LocationState())); return;
    //_game->setState(new CritterDialogState()); return;
    if (_splashTicks + 3000 < SDL_GetTicks())
    {
        //_game->setPlayer(new Player(ResourceManager::gcdFileType("premade/combat.gcd")));
        //_game->setState(new SettingsMenuState(_game));
        Game::getInstance()->setState(std::shared_ptr<MainMenuState>(new MainMenuState()));
    }    
}

}

