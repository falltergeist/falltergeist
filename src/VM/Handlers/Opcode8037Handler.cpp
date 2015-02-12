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
#include "../../VM/Handlers/Opcode8037Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8037Handler::Opcode8037Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8037Handler::_run()
{
    auto b = _vm->popDataInteger();
    auto a = _vm->popDataInteger();
    auto result = a < b;

    Logger::debug("SCRIPT") << "[8037] [*] lt (a < b)" << std::endl
                            << "    a = " << a << std::endl
                            << "    b = " << b << std::endl
                            << "    result = " << result << std::endl;

    _vm->pushDataInteger(result);
}

}
