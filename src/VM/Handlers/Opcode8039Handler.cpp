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
    debug << "[8039] [*] value = value1 + value2" << std::endl;
    auto b = _vm->dataStack()->top();
    switch (b->type())
    {
        case VMStackValue::TYPE_POINTER: // STRING
        {
            std::string string2;
            switch(((VMStackPointerValue*)b)->pointerType())
            {
                case VMStackPointerValue::POINTER_TYPE_STRING:
                    string2 = *static_cast<std::string*>(_vm->popDataPointer());
                    break;
                default:
                    _vm->popDataPointer();
                    string2 = "UNSUPPORTED";
                    break;
            }
            auto a = _vm->dataStack()->top();
            switch(a->type())
            {
                case VMStackValue::TYPE_POINTER: // STRING + STRING
                {
                    auto p1 = static_cast<std::string*>(_vm->popDataPointer());
                    std::string string1 = (p1 ? *p1 : "");
                    _vm->pushDataPointer(new std::string(string1 + string2), VMStackPointerValue::POINTER_TYPE_STRING);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + STRING
                {
                    throw Exception("VM::opcode PLUS - FLOAT+POINTER not allowed");
                }
                case VMStackValue::TYPE_INTEGER: // INTEGER + STRING
                {
                    throw Exception("VM::opcode PLUS - INTEGER+POINTER not allowed");
                }
            }
            break;
        }
        case VMStackValue::TYPE_INTEGER: // INTEGER
        {
            auto p2 = _vm->popDataInteger();
            auto a = _vm->dataStack()->top();
            debug << "    value2 type: " << a->type() << std::endl;
            switch(a->type())
            {
                case VMStackValue::TYPE_INTEGER: // INTEGER + INTEGER
                {
                    auto p1 = _vm->popDataInteger();
                    _vm->pushDataInteger(p1 + p2);
                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + INTEGER
                {
                    auto p1 = _vm->popDataFloat();
                    _vm->pushDataFloat(p1 + p2);
                    break;
                }
                case VMStackValue::TYPE_POINTER: // STRING + INTEGER
                {
                    auto p1 = static_cast<std::string*>(_vm->popDataPointer());
                    std::string string1 = (p1 ? *p1 : "");
                    _vm->pushDataPointer(new std::string(string1 + std::to_string(p2)), VMStackPointerValue::POINTER_TYPE_STRING);
                    break;
                }
            }
            break;
        }
        case VMStackValue::TYPE_FLOAT: // FLOAT
        {
            auto p2 = _vm->popDataFloat();
            auto a = _vm->dataStack()->top();
            debug << "    value2 type: " << a->type() << std::endl;
            switch(a->type())
            {
                case VMStackValue::TYPE_INTEGER: // INTEGER + FLOAT
                {
                    auto p1 = _vm->popDataInteger();
                    _vm->pushDataFloat(p1 + p2);

                    break;
                }
                case VMStackValue::TYPE_FLOAT: // FLOAT + FLOAT
                {
                    auto p1 = _vm->popDataFloat();
                    _vm->pushDataFloat(p1 + p2);
                    break;
                }
                case VMStackValue::TYPE_POINTER: // STRING + FLOAT
                {
                    auto p1 = static_cast<std::string*>(_vm->popDataPointer());
                    std::string string1 = (p1 ? *p1 : "");

                    _vm->pushDataPointer(new std::string(string1 + std::to_string(p2)), VMStackPointerValue::POINTER_TYPE_STRING);
                    break;
                }
            }
            break;
        }
    }
}

}
