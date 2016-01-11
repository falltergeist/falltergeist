/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../../VM/Handlers/Opcode803AHandler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode803AHandler::Opcode803AHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode803AHandler::_run()
{
    Logger::debug("SCRIPT") << "[803A] [*] op_sub(a, b) -" << std::endl;
    auto bValue = _vm->dataStack()->pop();
    auto aValue = _vm->dataStack()->pop();
    if (!bValue.isNumber() || !aValue.isNumber())
    {
        _error(std::string("op_sub(a, b): Incompatible types: ") + aValue.typeName() + " - " + bValue.typeName());
    }
    if (aValue.type() == VMStackValue::Type::INTEGER)
    {
        if (bValue.type() == VMStackValue::Type::INTEGER)
        {
            _vm->dataStack()->push(aValue.integerValue() - bValue.integerValue());
        }
        else
        {
            _vm->dataStack()->push((float)aValue.integerValue() - bValue.floatValue());
        }
    }
    else
    {
        if (bValue.type() == VMStackValue::Type::INTEGER)
        {
            _vm->dataStack()->push(aValue.floatValue() - (float)bValue.integerValue());
        }
        else
        {
            _vm->dataStack()->push(aValue.floatValue() - bValue.floatValue());
        }
    }
}

}
