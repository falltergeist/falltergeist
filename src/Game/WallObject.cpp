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
#include "WallObject.h"
#include "Game.h"
#include "DudeObject.h"
#include "../PathFinding/Hexagon.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameWallObject::GameWallObject() : GameObject()
{
    _type = TYPE_WALL;
}

GameWallObject::~GameWallObject()
{
}

void GameWallObject::think()
{
    GameObject::think();
    auto dude = Game::getInstance()->player();
    auto hex = dude->hexagon();

    int dx = (hexagon()->number() % 200) - (hex->number() % 200);
    int dy = (hexagon()->number() / 200) - (hex->number() / 200);

    if ((dx>0 && dx<3 && dy>0 && dy<3))// || (dy>0 && dy<3 && dx>-3 && dx<3))
    {
        _transparent = true;
    }
    else
    {
        _transparent = false;
    }
}

}
}
