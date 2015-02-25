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
#include "../../VM/Handlers/Opcode80ABHandler.h"
#include "../../VM/VM.h"




// Third party includes

namespace Falltergeist
{

Opcode80ABHandler::Opcode80ABHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80ABHandler::_run()
{
    // @TODO: implement
    Logger::debug("SCRIPT") << "[80AB] [=] int using_skill(GameCritterObject* who, int skill)" << std::endl;
<<<<<<< HEAD
    _vm->dataStack()->popInteger();
    _vm->dataStack()->popObject();
    _vm->dataStack()->push(0);
=======
    _vm->popDataInteger();
    _vm->popDataObject();
    _vm->pushDataInteger(0);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
}

}


