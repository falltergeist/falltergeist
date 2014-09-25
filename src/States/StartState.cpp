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
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameDudeObject.h"
#include "../States/CritterDialogState.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../States/SettingsMenuState.h"
#include "../States/StartState.h"
#include "../UI/Image.h"
#include "../Engine/Settings.h"

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

    auto renderer = Game::getInstance()->renderer();

    setX((renderer->width()  - 640)*0.5);
    setY((renderer->height() - 480)*0.5);

    srand(time(NULL)); // seed
    addUI("splash", new Image("art/splash/" + splashes.at(rand() % splashes.size())));

    _splashTicks = SDL_GetTicks();

    Game::getInstance()->mouse()->setType(Mouse::WAIT);
}

void StartState::think()
{
    auto game = Game::getInstance();
    State::think();
    if (game->engineSettings()->forceLocation())
    {
        auto player = new GameDudeObject();
        player->loadFromGCDFile(ResourceManager::gcdFileType("premade/combat.gcd"));
        game->setPlayer(player);
        game->setState(new LocationState());
        return;
    }
    if (_splashTicks + 3000 < SDL_GetTicks())
    {
        game->setState(new MainMenuState());
    }
}

}

