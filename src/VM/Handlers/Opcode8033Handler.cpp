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
#include "../../VM/Handlers/Opcode8033Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode8033Handler::Opcode8033Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8033Handler::_run()
{
    Logger::debug("SCRIPT") << "[8033] [*] op_equal ==" << std::endl;
    switch (_vm->dataStack()->top()->type())
    {
        case VMStackValue::TYPE_INTEGER:
        {
            auto p2 = _vm->dataStack()->popInteger();
            switch (_vm->dataStack()->top()->type())
            {
                case VMStackValue::TYPE_INTEGER:
                {
                    auto p1 = _vm->dataStack()->popInteger();
                    _vm->dataStack()->push(p1 == p2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT:
                {
                    auto p1 = _vm->dataStack()->popFloat();
                    _vm->dataStack()->push(p1 == p2);
                    break;
                }
                case VMStackValue::TYPE_OBJECT:
                {
                    auto p1 = (int)(bool)_vm->dataStack()->popObject();
                    _vm->dataStack()->push(p1 == p2);
                    break;
                }
            }
            break;
        }
        case VMStackValue::TYPE_OBJECT:
        {
            // @TODO: proper string comparison
            auto p2 = _vm->dataStack()->popObject();
            auto p1 = _vm->dataStack()->popObject();
            _vm->dataStack()->push(p1 == p2);
            break;
        }
        case VMStackValue::TYPE_FLOAT:
        {
            auto p2 = _vm->dataStack()->popFloat();
            auto p1 = _vm->dataStack()->popFloat();
            _vm->dataStack()->push(p1 == p2);
            break;
        }
    }
}

}
