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
#include "../../VM/Handlers/OpcodeC001Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackIntValue.h"

// Third party includes

namespace Falltergeist
{

OpcodeC001Handler::OpcodeC001Handler(VM* vm) : OpcodeHandler(vm)
{
}

void OpcodeC001Handler::_run()
{
    int value;
    *(_vm->script()) >> value;

    // Skip 4 bytes for readed integer value
    _vm->setProgramCounter(_vm->programCounter() + 4);
    _vm->dataStack()->push(std::shared_ptr<VMStackIntValue>(new VMStackIntValue(value)));

    Logger::info("SCRIPT") << "[C001] [*] push_d 0x" << std::hex << value << std::endl;
}

}
