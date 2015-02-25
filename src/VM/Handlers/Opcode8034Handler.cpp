/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include "../../VM/Handlers/Opcode8034Handler.h"
#include "../../VM/VMStackValue.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8034Handler::Opcode8034Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8034Handler::_run()
{
    switch (_vm->dataStack()->top()->type())
    {
        case VMStackValue::TYPE_INTEGER:
        {
            auto p2 = _vm->dataStack()->popInteger();
            if (_vm->dataStack()->top()->type() == VMStackValue::TYPE_OBJECT) // to check if the pointer is null
            {
                auto p1 = (int)(bool)_vm->dataStack()->popObject();
                _vm->dataStack()->push(p1 != p2);
            }
            else
            {
                auto p1 = _vm->dataStack()->popInteger();
                _vm->dataStack()->push(p1 != p2);
            }
            break;
        }
        case VMStackValue::TYPE_OBJECT:
        {
            // @TODO: add string comparison
            auto p2 = (int)(bool)_vm->dataStack()->popObject();
            if (_vm->dataStack()->top()->type() == VMStackValue::TYPE_OBJECT) // to check if the pointer is null
            {
                auto p1 = (int)(bool)_vm->dataStack()->popObject();
                _vm->dataStack()->push(p1 != p2);
            }
            else
            {
                auto p1 = _vm->dataStack()->popInteger();
                _vm->dataStack()->push(p1 != p2);
            }
            break;
        }
        case VMStackValue::TYPE_FLOAT:
        {
            auto p2 = _vm->dataStack()->popFloat();
            auto p1 = _vm->dataStack()->popFloat();
            _vm->dataStack()->push(p1 != p2);
            break;
        }
    }
    Logger::debug("SCRIPT") << "[8034] [*] op_not_equal !=" << std::endl;

}

}
