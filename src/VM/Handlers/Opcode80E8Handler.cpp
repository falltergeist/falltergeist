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
#include "../../Game/CritterObject.h"
#include "../../VM/Handlers/Opcode80E8Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80E8Handler::Opcode80E8Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80E8Handler::_run()
{
    int amount = _vm->popDataInteger();
    auto critter = static_cast<Game::GameCritterObject*>(_vm->popDataObject());
    if (!critter)
    {
        throw Exception("VM::opcode80E8 pointer error");
    }
    critter->setHitPoints(critter->hitPoints() + amount);

    auto &debug = Logger::debug("SCRIPT");
    debug << "[80E8] [+] void critter_heal(ObjectPtr who, int amount)" << std::endl;
    debug << "    amount = " << amount << std::endl;
}

}
