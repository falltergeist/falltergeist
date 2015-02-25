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
#include "../../Exception.h"
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode8039Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode8039Handler::Opcode8039Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8039Handler::_run()
{
    auto& debug = Logger::debug("SCRIPT");
    debug << "[8039] [*] op_add(aValue, bValue)" << std::endl;
    auto bValue = _vm->dataStack()->top();
    switch (bValue.type())
    {
        case VMStackValue::TYPE_STRING: 
        {
            auto arg2 = _vm->dataStack()->popString();
            auto aValue = _vm->dataStack()->top();
            switch (aValue.type())
            {
                case VMStackValue::TYPE_STRING: // STRING + STRING
                {
                    std::string arg1 = _vm->dataStack()->popString();
                    _vm->dataStack()->push(arg1 + arg2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + STRING
                {
                    throw Exception("VM::opcode PLUS - FLOAT+STRING not allowed");
                }
                case VMStackValue::TYPE_INTEGER: // INTEGER + STRING
                {
                    throw Exception("VM::opcode PLUS - INTEGER+STRING not allowed");
                }
                default:
                {
                    throw Exception("VM::opcode PLUS - invalid left argument type: " + aValue.typeName());
                }
            }
            break;
        }
        case VMStackValue::TYPE_INTEGER: // INTEGER
        {
            auto arg2 = _vm->dataStack()->popInteger();
            auto aValue = _vm->dataStack()->top();
            debug << "    value2 type: " << aValue.typeName() << std::endl;
            switch (aValue.type())
            {
                case VMStackValue::TYPE_INTEGER: // INTEGER + INTEGER
                {
                    int arg1 = _vm->dataStack()->popInteger();
                    _vm->dataStack()->push(arg1 + arg2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + INTEGER
                {
                    float arg1 = _vm->dataStack()->popFloat();
                    _vm->dataStack()->push(arg1 + arg2);
                    break;
                }
                case VMStackValue::TYPE_STRING: // STRING + INTEGER
                {
                    std::string arg1 = _vm->dataStack()->popString();
                    _vm->dataStack()->push(arg1 + bValue.toString());
                    break;
                }
                default:
                {
                    throw Exception("VM::opcode PLUS - invalid left argument type: " + aValue.typeName());
                }
            }
            break;
        }
        case VMStackValue::TYPE_FLOAT: // FLOAT
        {
            auto arg2 = _vm->dataStack()->popFloat();
            auto aValue = _vm->dataStack()->top();
            debug << "    value2 type: " << aValue.typeName() << std::endl;
            switch (aValue.type())
            {
                case VMStackValue::TYPE_INTEGER: // INTEGER + FLOAT
                {
                    auto arg1 = _vm->dataStack()->popInteger();
                    _vm->dataStack()->push(arg1 + arg2);

                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + FLOAT
                {
                    auto arg1 = _vm->dataStack()->popFloat();
                    _vm->dataStack()->push(arg1 + arg2);
                    break;
                }
                case VMStackValue::TYPE_OBJECT: // STRING + FLOAT
                {
                    auto arg1 = _vm->dataStack()->popString();
                    _vm->dataStack()->push(arg1 + bValue.toString());
                    break;
                }
                default:
                {
                    throw Exception("VM::opcode PLUS - invalid left argument type: " + aValue.typeName());
                }
            }
            break;
        }
        default:
        {
            throw Exception("VM::opcode PLUS - invalid right argument type: " + bValue.typeName());
        }
    }
}

}
