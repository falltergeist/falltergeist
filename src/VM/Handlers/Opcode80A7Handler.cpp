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

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80A7Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/VM.h"


// Third party includes

namespace Falltergeist
{

Opcode80A7Handler::Opcode80A7Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80A7Handler::_run()
{
    Logger::debug("SCRIPT") << "[80A7] [+] GameObject* tile_contains_pid_obj(int position, int elevation, int PID)" << std::endl;
    auto PID = _vm->dataStack()->popInteger();
    auto elevation = _vm->dataStack()->popInteger();
    auto position = _vm->dataStack()->popInteger();
    auto game = Game::getInstance();
    Game::GameObject* found = nullptr;
    for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects())
    {
        if (object->PID() == PID && object->elevation() == elevation)
        {
            found = object;
            break;
        }
    }
<<<<<<< HEAD
    _vm->dataStack()->push(found);
=======
    _vm->pushDataObject(found);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
}

}


