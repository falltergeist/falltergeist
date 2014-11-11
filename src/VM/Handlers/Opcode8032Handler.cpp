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
#include "../../Engine/Logger.h"
#include "../../VM/Handlers/Opcode8032Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8032Handler::Opcode8032Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8032Handler::_run()
{
    auto num = _vm->popDataInteger();
    auto value = _vm->dataStack()->values()->at(_vm->DVARbase() + num);
    _vm->dataStack()->push(value);
    Logger::debug("SCRIPT") << "[8032] [*] DVAR[num] " << "num = " << std::hex << num << " type = " << value->type() << std::endl;
}

}
