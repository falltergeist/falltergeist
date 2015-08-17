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

// C++ standard includes
#include <vector>
#include <string>
#include <ctime>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../Game/DudeObject.h"
#include "../State/CritterDialog.h"
#include "../State/MainMenu.h"
#include "../State/Movie.h"
#include "../State/Location.h"
#include "../State/SettingsMenu.h"
#include "../State/Start.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

Start::Start() : State()
{
}

Start::~Start()
{
}

void Start::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    std::vector<std::string> splashes = {"splash0.rix", "splash1.rix", "splash2.rix", "splash3.rix", "splash4.rix", "splash5.rix", "splash6.rix"};

    auto renderer = Game::getInstance()->renderer();

    setX((renderer->width()  - 640)*0.5);
    setY((renderer->height() - 480)*0.5);

    srand(time(NULL)); // seed
    addUI("splash", new Image("art/splash/" + splashes.at(rand() % splashes.size())));

    _splashTicks = SDL_GetTicks();

    Game::getInstance()->mouse()->setState(Mouse::Cursor::WAIT);
}

void Start::think()
{
    auto game = Game::getInstance();
    State::think();
    if (game->settings()->forceLocation())
    {
        auto player = new Game::DudeObject();
        player->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
        game->setPlayer(player);
        game->setState(new Location());
        return;
    }
    if (_splashTicks + 3000 < SDL_GetTicks())
    {
        game->setState(new MainMenu());
        game->pushState(new Movie(17));
        game->pushState(new Movie(1));
        game->pushState(new Movie(0));
    }
}

}
}
