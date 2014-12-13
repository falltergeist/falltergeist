/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include <string>
// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80B8Handler.h"
#include "../../VM/VM.h"




// Third party includes

namespace Falltergeist
{

Opcode80B8Handler::Opcode80B8Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80B8Handler::_run()
{
    Logger::debug("SCRIPT") << "[80B8] [*] void display_msg(string*)" << std::endl;
    std::string* pointer = static_cast<std::string*>(_vm->popDataPointer());
    Logger::debug("SCRIPT") << *pointer << std::endl;
}

}


