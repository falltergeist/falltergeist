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
#include <sstream>

// Falltergeist includes
#include "../../VM/Handlers/Opcode8005Handler.h"
#include "../../VM/VM.h"
#include "../../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

Opcode8005Handler::Opcode8005Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8005Handler::run()
{
    OpcodeHandler::run();

    auto functionIndex = _vm->popDataInteger();
    _vm->setProgramCounter(_vm->script()->function(functionIndex));

    // Loging
    std::ostringstream ss;
    ss << "[*] call(0x" << std::hex << functionIndex << ") = 0x" << _vm->programCounter();
    CrossPlatform::debug(ss.str(), DEBUG_SCRIPT);
}

}
