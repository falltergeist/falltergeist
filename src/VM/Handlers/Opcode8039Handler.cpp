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
    auto bValue = _vm->dataStack()->pop();
    auto aValue = _vm->dataStack()->pop();
    debug << "    types: " << aValue.typeName() << " + " << bValue.typeName() << std::endl;
    switch (bValue.type())
    {
<<<<<<< HEAD
        case VMStackValue::TYPE_INTEGER: // INTEGER
=======
        case VMStackValue::TYPE_OBJECT: // STRING
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
        {
            int arg2 = bValue.integerValue();
            switch (aValue.type())
            {
<<<<<<< HEAD
                case VMStackValue::TYPE_INTEGER: // INTEGER + INTEGER
                {
                    _vm->dataStack()->push(aValue.integerValue() + arg2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + INTEGER
                {
                    _vm->dataStack()->push(aValue.floatValue() + (float)arg2);
=======
                case VMStackPointerValue::POINTER_TYPE_STRING:
                    string2 = *static_cast<std::string*>(_vm->popDataObject());
                    break;
                default:
                    _vm->popDataObject();
                    string2 = "UNSUPPORTED";
                    break;
            }
            auto a = _vm->dataStack()->top();
            switch(a->type())
            {
                case VMStackValue::TYPE_OBJECT: // STRING + STRING
                {
                    auto p1 = static_cast<std::string*>(_vm->popDataObject());
                    std::string string1 = (p1 ? *p1 : "");
                    _vm->pushDataObject(new std::string(string1 + string2), VMStackPointerValue::POINTER_TYPE_STRING);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
                    break;
                }
                case VMStackValue::TYPE_STRING: // STRING + INTEGER
                {
                    std::string arg1 = aValue.stringValue();
                    _vm->dataStack()->push(arg1 + bValue.toString());
                    break;
                }
                default:
                {
                    _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                }
            }
            break;
        }
        case VMStackValue::TYPE_STRING: 
        {
            auto arg2 = bValue.stringValue();
            switch (aValue.type())
            {
                case VMStackValue::TYPE_STRING: // STRING + STRING
                {
                    _vm->dataStack()->push(aValue.stringValue() + arg2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + STRING
                {
                    _error("op_add - FLOAT+STRING not allowed");
                }
                case VMStackValue::TYPE_INTEGER: // INTEGER + STRING
                {
                    _error("op_add - INTEGER+STRING not allowed");
                }
<<<<<<< HEAD
                default:
                {
                    _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
=======
                case VMStackValue::TYPE_OBJECT: // STRING + INTEGER
                {
                    auto p1 = static_cast<std::string*>(_vm->popDataObject());
                    std::string string1 = (p1 ? *p1 : "");
                    _vm->pushDataObject(new std::string(string1 + std::to_string(p2)), VMStackPointerValue::POINTER_TYPE_STRING);
                    break;
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
                }
            }
            break;
        }
        case VMStackValue::TYPE_FLOAT: // FLOAT
        {
            auto arg2 = bValue.floatValue();
            switch (aValue.type())
            {
                case VMStackValue::TYPE_INTEGER: // INTEGER + FLOAT
                {
                    _vm->dataStack()->push((float)aValue.integerValue() + arg2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + FLOAT
                {
                    _vm->dataStack()->push(aValue.floatValue() + arg2);
                    break;
                }
<<<<<<< HEAD
                case VMStackValue::TYPE_STRING: // STRING + FLOAT
                {
                    auto arg1 = aValue.stringValue();
                    _vm->dataStack()->push(arg1 + bValue.toString());
=======
                case VMStackValue::TYPE_OBJECT: // STRING + FLOAT
                {
                    auto p1 = static_cast<std::string*>(_vm->popDataObject());
                    std::string string1 = (p1 ? *p1 : "");

                    _vm->pushDataObject(new std::string(string1 + std::to_string(p2)), VMStackPointerValue::POINTER_TYPE_STRING);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
                    break;
                }
                default:
                {
                    _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                }
            }
            break;
        }
        default:
        {
            _error(std::string("op_add - invalid right argument type: ") + bValue.typeName());
        }
    }
}

}
