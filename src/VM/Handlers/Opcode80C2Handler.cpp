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
#include "../../VM/Handlers/Opcode80C2Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackIntValue.h"




// Third party includes

namespace Falltergeist
{

Opcode80C2Handler::Opcode80C2Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80C2Handler::_run()
{
    Logger::debug("SCRIPT") << "[80C2] [*] LVAR[num] = value" << std::endl;
    auto value = _vm->dataStack()->pop();
    unsigned int num = _vm->popDataInteger();
    while (num >= _vm->LVARS()->size()) _vm->LVARS()->push_back(new VMStackIntValue(0));
    _vm->LVARS()->at(num) = value;
}

}


