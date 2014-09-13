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

// Falltergeist includes
#include "../States/GameMenuState.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

GameMenuState::GameMenuState()
{
}

void GameMenuState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/opbase.frm"));

    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;

    background->setX(backgroundX);
    background->setY(backgroundY);

    add(background);
}

}
