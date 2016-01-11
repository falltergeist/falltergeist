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
#include "../../VM/Handlers/Opcode800DHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode800DHandler::Opcode800DHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode800DHandler::_run()
{
    Logger::debug("SCRIPT") << "[800D] [*] op_d_to_a" << std::endl;
    _vm->returnStack()->push(_vm->dataStack()->pop());
}

}
