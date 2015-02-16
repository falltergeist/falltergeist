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
#include "../../VM/Handlers/Opcode8013Handler.h"
#include "../../VM/VMStackValue.h"
#include "../../VM/VMStackFloatValue.h"
#include "../../VM/VMStackIntValue.h"
#include "../../VM/VMStackPointerValue.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8013Handler::Opcode8013Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8013Handler::_run()
{
    auto number = _vm->popDataInteger();
    auto value = _vm->dataStack()->pop();
    _vm->dataStack()->values()->at(_vm->SVARbase() + number) = value;

    auto& debug = Logger::debug("SCRIPT");

    debug   << "[8013] [*] op_store_global" << std::endl
            << "      num: "  << number << std::endl
            << "     type: " << value->type() << std::endl
            << "    value: ";

    switch (value->type())
    {
        case VMStackValue::TYPE_INTEGER:
            debug << ((VMStackIntValue*)value)->value();
            break;
        case VMStackValue::TYPE_FLOAT:
            debug << ((VMStackFloatValue*)value)->value();
            break;
        case VMStackValue::TYPE_POINTER:
            debug << ((VMStackPointerValue*)value)->value();
            break;
    }
    debug << std::endl;
}

}
