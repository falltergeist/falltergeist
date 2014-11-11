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
#include <cstdlib>
#include <ctime>
// Falltergeist includes
#include "../../Engine/Logger.h"
#include "../../VM/Handlers/Opcode80B4Handler.h"
#include "../../VM/VM.h"




// Third party includes

namespace Falltergeist
{

Opcode80B4Handler::Opcode80B4Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80B4Handler::_run()
{
   Logger::debug("SCRIPT") << "[80B4] [+] int rand(int min, int max)" << std::endl;
   auto max = _vm->popDataInteger();
   auto min = _vm->popDataInteger();
   srand(time(0));
   _vm->pushDataInteger(rand()%(max - min + 1) + min);
}

}


