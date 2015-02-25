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
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80FFHandler.h"
#include "../../Exception.h"
#include "../../Game/Game.h"
#include "../../ResourceManager.h"
#include "../../Game/Object.h"
#include "../../Game/CritterObject.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80FFHandler::Opcode80FFHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80FFHandler::_run()
{
    Logger::debug("SCRIPT") << "[80FF] [*] int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)" << std::endl;
    auto elevation = _vm->dataStack()->popInteger();
    auto position = _vm->dataStack()->popInteger();
    auto critter = static_cast<Game::GameCritterObject*>(_vm->dataStack()->popObject());
    if (!critter) throw new Exception("Opcode 80ff error");
    auto hexagon = Game::getInstance()->locationState()->hexagonGrid()->at(position);
    State::Location::moveObjectToHexagon(critter, hexagon);
    critter->setElevation(elevation);
    _vm->dataStack()->push(1);
}

}


