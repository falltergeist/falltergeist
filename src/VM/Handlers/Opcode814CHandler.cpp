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

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode814CHandler.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode814CHandler::Opcode814CHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode814CHandler::_run()
{
    Logger::debug("SCRIPT") << "[814C] [=] int rotation_to_tile(int srcTile, int destTile)" << std::endl;
    _vm->popDataInteger();
    _vm->popDataInteger();
    _vm->pushDataInteger(0);
}

}

