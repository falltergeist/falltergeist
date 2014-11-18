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
#include "../../Engine/Exception.h"
#include "../../Engine/Logger.h"
#include "../../VM/Handlers/Opcode80E1Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80E1Handler::Opcode80E1Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80E1Handler::_run()
{
    Logger::debug("SCRIPT") << "[80E1] [*] int metarule3(int meta, int p1, int p2, int p3)" << std::endl;
    auto p3 = _vm->popDataInteger();
    auto p2 = _vm->popDataInteger();
    auto p1 = _vm->dataStack()->pop();
    auto meta = _vm->popDataInteger();
    int result;
    switch(meta)
    {
        case 100: // rm_fixed_timer_event
            result = 0;
            break;
        case 110:   // unknown
            result = 0;
            break;
        default:
            throw Exception("Opcode80E11Handler - unknown meta: " + std::to_string(meta));
            break;
    }
    _vm->pushDataInteger(result);
}

}
