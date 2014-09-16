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
#include "../../VM/Handlers/Opcode8034Handler.h"
#include "../../VM/VMStackValue.h"
#include "../../VM/VM.h"
#include "../../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

Opcode8034Handler::Opcode8034Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8034Handler::run()
{
    OpcodeHandler::run();

    switch (_vm->dataStack()->top()->type())
    {
        case VMStackValue::TYPE_INTEGER:
        {
            auto p2 = _vm->popDataInteger();
            if (_vm->dataStack()->top()->type() == VMStackValue::TYPE_POINTER) // to check if the pointer is null
            {
                auto p1 = (int)(bool)_vm->popDataPointer();
                _vm->pushDataInteger(p1 != p2);
            }
            else
            {
                auto p1 = _vm->popDataInteger();
                _vm->pushDataInteger(p1 != p2);
            }
            break;
        }
        case VMStackValue::TYPE_POINTER:
        {
            auto p2 = (int)(bool)_vm->popDataPointer();
            if (_vm->dataStack()->top()->type() == VMStackValue::TYPE_POINTER) // to check if the pointer is null
            {
                auto p1 = (int)(bool)_vm->popDataPointer();
                _vm->pushDataInteger(p1 != p2);
            }
            else
            {
                auto p1 = _vm->popDataInteger();
                _vm->pushDataInteger(p1 != p2);
            }
            break;
        }
        case VMStackValue::TYPE_FLOAT:
        {
            auto p2 = _vm->popDataFloat();
            auto p1 = _vm->popDataFloat();
            _vm->pushDataInteger(p1 != p2);
            break;
        }
    }
    CrossPlatform::debug("[*] neq !=", DEBUG_SCRIPT);

}

}
