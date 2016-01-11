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
#include "../../VM/Handlers/Opcode80B6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/DudeObject.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/VM.h"




// Third party includes

namespace Falltergeist
{

Opcode80B6Handler::Opcode80B6Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80B6Handler::_run()
{
    Logger::debug("SCRIPT") << "[80B6] [+] int move_to(GameObject* object, int position, int elevation)" << std::endl;
    auto elevation = _vm->dataStack()->popInteger();
    auto position = _vm->dataStack()->popInteger();
    auto object = _vm->dataStack()->popObject();
    if (!object) 
    {
        _error("move_to: object is NULL");
    }
    auto hexagon = Game::getInstance()->locationState()->hexagonGrid()->at(position);
    State::Location::moveObjectToHexagon(object, hexagon);
    object->setElevation(elevation);
    if (object == Game::getInstance()->player()) {
        Game::getInstance()->locationState()->centerCameraAtHexagon(object->hexagon());
    }
    _vm->dataStack()->push(0);
}

}
