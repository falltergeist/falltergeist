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
#include "../../VM/Handlers/Opcode8106Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/CritterObject.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode8106Handler::Opcode8106Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8106Handler::_run()
{
    Logger::debug("SCRIPT") << "[8106] [=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)" << std::endl;
<<<<<<< HEAD
    auto where = _vm->dataStack()->popInteger();
    auto critter = dynamic_cast<Game::GameCritterObject*>(_vm->dataStack()->popObject());
    switch (where)
    {
    case 0: // ARMOR SLOT
        _vm->dataStack()->push(critter->armorSlot());
        break;
    case 1: // RIGHT HAND SLOT
        _vm->dataStack()->push(critter->rightHandSlot());
        break;
    case 2: // LEFT HAND SLOT
        _vm->dataStack()->push(critter->leftHandSlot());
=======
    auto where = _vm->popDataInteger();
    auto critter = static_cast<Game::GameCritterObject*>(_vm->popDataObject());
    switch (where)
    {
    case 0: // ARMOR SLOT
        _vm->pushDataObject(critter->armorSlot());
        break;
    case 1: // RIGHT HAND SLOT
        _vm->pushDataObject(critter->rightHandSlot());
        break;
    case 2: // LEFT HAND SLOT
        _vm->pushDataObject(critter->leftHandSlot());
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
        break;
    case -2: // INVENTORY COUNT
        _vm->dataStack()->push((unsigned int)critter->inventory()->size());
        break;
    default:
        _error(std::string("critter_inven_obj - invalid slot: ") + std::to_string(where));
    }
}

}


