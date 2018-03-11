/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#include "GameBootingState.h"

#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Helpers/StateLocationHelper.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/CritterDialog.h"
#include "../State/Location.h"
#include "../State/MainMenu.h"
#include "../State/Movie.h"
#include "../State/SettingsMenu.h"

#include <ctime>

namespace Falltergeist
{
    using Helpers::StateLocationHelper;

    namespace State
    {
        GameBootingState::GameBootingState() : State()
        {
        }

        GameBootingState::~GameBootingState()
        {
        }

        void GameBootingState::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);

            std::vector<std::string> splashes = {"splash0.rix", "splash1.rix", "splash2.rix", "splash3.rix", "splash4.rix", "splash5.rix", "splash6.rix"};

            auto renderer = Game::getInstance()->renderer();

            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("splash", new UI::Image("art/splash/" + splashes.at(rand() % splashes.size())));

            _splashTicks = SDL_GetTicks();

            Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::WAIT);
        }

        void GameBootingState::think()
        {
            auto game = Game::getInstance();
            State::think();
            if (game->settings()->forceLocation())
            {
                auto player = std::make_unique<Game::DudeObject>();
                player->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
                game->setPlayer(std::move(player));

                StateLocationHelper stateLocationHelper;
                game->setState(stateLocationHelper.getInitialLocationState());
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
