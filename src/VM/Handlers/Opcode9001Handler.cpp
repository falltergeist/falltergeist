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
#include "../../VM/Handlers/Opcode9001Handler.h"
#include "../../VM/VM.h"
#include "../../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

Opcode9001Handler::Opcode9001Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode9001Handler::_run()
{
    unsigned int value;
    unsigned short nextOpcode;
    *(_vm->script()) >> value >> nextOpcode;

    // Skip 4 readed bytes
    _vm->setProgramCounter(_vm->programCounter() + 4);

    switch(nextOpcode)
    {
        case 0x8014: // get exported var value
        case 0x8015: // set exported var value
        case 0x8016: // export var
        {
            auto pointer = std::shared_ptr<std::string>(new std::string(_vm->script()->identificators()->at(value)));
            _vm->pushDataPointer(pointer);
            CrossPlatform::debug("[*] push_d *" + std::to_string((unsigned long long) pointer.get()), DEBUG_SCRIPT);
            break;
        }
        default:
        {
            auto pointer = std::shared_ptr<std::string>(new std::string(_vm->script()->strings()->at(value)));
            _vm->pushDataPointer(pointer);
            CrossPlatform::debug("[*] push_d *" + std::to_string((unsigned long long) pointer.get()), DEBUG_SCRIPT);
            break;
         }
    }
}

}
