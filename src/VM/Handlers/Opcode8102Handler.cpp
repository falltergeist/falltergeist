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
#include "../../VM/Handlers/Opcode8102Handler.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode8102Handler::Opcode8102Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8102Handler::_run()
{
    Logger::debug("SCRIPT") << "[8102] [*] int critter_add_trait(void* who, int trait_type, int trait, int amount) " << std::endl;
    auto amount = _vm->dataStack()->popInteger();
    auto trait = _vm->dataStack()->popInteger();
    auto trait_type = _vm->dataStack()->popInteger();
    auto who = _vm->dataStack()->popObject();

    UNUSED_ARG(amount);
    UNUSED_ARG(trait);
    UNUSED_ARG(trait_type);
    UNUSED_ARG(who);
    _vm->dataStack()->push(0);
}

}


