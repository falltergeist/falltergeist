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
#include "../../VM/Handlers/Opcode9001Handler.h"
#include "../../VM/VMStackValue.h"
#include "../../VM/VMStackPointerValue.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode9001Handler::Opcode9001Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode9001Handler::_run()
{
    unsigned int data;
    unsigned short nextOpcode;
    *(_vm->script()) >> data >> nextOpcode;

    // Skip 4 readed bytes
    _vm->setProgramCounter(_vm->programCounter() + 4);

    std::string* pointer;
    switch(nextOpcode)
    {
        case 0x8014: // get exported var value
        case 0x8015: // set exported var value
        case 0x8016: // export var
        {
            pointer = new std::string(_vm->script()->identificators()->at(data));
            _vm->pushDataPointer(pointer, VMStackPointerValue::POINTER_TYPE_STRING);
            break;
        }
        default:
        {
            pointer = new std::string(_vm->script()->strings()->at(data));
            _vm->pushDataPointer(pointer, VMStackPointerValue::POINTER_TYPE_STRING);
            break;
        }
    }

    auto value = _vm->dataStack()->top();

    auto string = static_cast<std::string*>(((VMStackPointerValue*)value)->value());

    auto& debug = Logger::debug("SCRIPT");
        debug << "[9001] [*] push_d value" << std::endl
              << "     type: " << value->type() << std::endl
              << "    value: " << ((VMStackPointerValue*)value)->value() << std::endl
              << "   string: " << *string << std::endl;
}

}
