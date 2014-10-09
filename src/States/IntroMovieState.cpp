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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Event/KeyboardEvent.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/MvePlayer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../States/IntroMovieState.h"
#include "../States/MainMenuState.h"

// Third party includes

namespace Falltergeist
{

IntroMovieState::IntroMovieState()
{
}

IntroMovieState::~IntroMovieState()
{
    delete _player;
}

void IntroMovieState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(true);
    setModal(true);

    Game::getInstance()->mouse()->pushState(Mouse::NONE);

    _player = new MvePlayer(ResourceManager::mveFileType("art/cuts/intro.mve").get());
    _player->play();
}

void IntroMovieState::think()
{
    State::think();
    _player->think();

    if (_player->finished())
    {
        this->onVideoFinished();
    }
}

void IntroMovieState::render()
{
    State::render();
    _player->render();
}

void IntroMovieState::handle(Event* event)
{
    if (auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        if (mouseEvent->name() == "mouseup")
        {
            this->onVideoFinished();
        }
    }

    if (auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        this->onVideoFinished();
    }
}

void IntroMovieState::onVideoFinished()
{
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->setState(new MainMenuState());
}

}
