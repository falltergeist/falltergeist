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
#include "../../VM/Handlers/Opcode8031Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8031Handler::Opcode8031Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8031Handler::_run()
{
    auto num = _vm->dataStack()->popInteger();
    auto value = _vm->dataStack()->pop();
    Logger::debug("SCRIPT") << "[8031] [*] op_store " << "var" << std::hex << num << " type = " << value.typeName() << std::endl;
    _vm->dataStack()->values()->at(_vm->DVARbase() + num) = value;
}

}
