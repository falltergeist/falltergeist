/*
 * Copyright 2012-2013 Falltergeist Developers.
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

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Player.h"
#include "../Engine/ResourceManager.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../States/PlayerEditState.h"
#include "../States/SettingsMenuState.h"
#include "../States/StartState.h"

// Third party includes

namespace Falltergeist
{

StartState::StartState(Game * game) : State(game)
{
    std::cout << "StartState..." << std::endl;
}

StartState::~StartState()
{
}

void StartState::think()
{
    //_game->setPlayer(new Player(ResourceManager::gcdFileType("premade/combat.gcd")));
    //_game->setState(new LocationState(_game));
    //_game->setState(new SettingsMenuState(_game));
    _game->setState(new MainMenuState(_game));
}

}

