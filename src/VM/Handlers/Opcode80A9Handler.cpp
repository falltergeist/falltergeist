/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80A9Handler.h"
#include "../../Game/Game.h"
#include "../../Game/DudeObject.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80A9Handler::Opcode80A9Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80A9Handler::_run()
{
    Logger::debug("SCRIPT") << "[80A9] [+] void override_map_start(int x, int y, int elevation, int orientation)" << std::endl;
    auto orientation = _vm->dataStack()->popInteger();
    auto elevation = _vm->dataStack()->popInteger();
    auto y = _vm->dataStack()->popInteger();
    auto x = _vm->dataStack()->popInteger();
    auto position = y*200 + x;
    auto game = Game::Game::getInstance();
    auto player = game->player();
    auto hexagon = game->locationState()->hexagonGrid()->at(position);
    Game::getInstance()->locationState()->moveObjectToHexagon(player, hexagon);
                //player->setPosition(position);
    player->setOrientation(orientation);
    player->setElevation(elevation);
    Game::Game::getInstance()->locationState()->centerCameraAtHexagon(player->hexagon());
}

}


