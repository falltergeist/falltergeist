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
#include "../../VM/Handlers/Opcode8046Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode8046Handler::Opcode8046Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8046Handler::_run()
{
    Logger::debug("SCRIPT") << "[8046] [*] op_negate" << std::endl;
    auto value = _vm->dataStack()->pop();
    if (value.type() == VMStackValue::Type::INTEGER)
    {
        _vm->dataStack()->push(- value.integerValue());
    }
    else if (value.type() == VMStackValue::Type::FLOAT)
    {
        _vm->dataStack()->push(- value.floatValue());
    }
    else
    {
        _error(std::string("Invalid argument type: ") + value.typeName());
    }
}

}


