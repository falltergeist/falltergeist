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
#include "../../Game/CritterObject.h"
#include "../../VM/Handlers/Opcode8122Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8122Handler::Opcode8122Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8122Handler::_run()
{
    auto &debug = Logger::debug("SCRIPT");
    debug << "[8122] [+] void poison(GameCritterObject* who, int amount)" << std::endl;
    int amount = _vm->dataStack()->popInteger();
    debug << "    amount = " << amount << std::endl;
    auto critter = dynamic_cast<Game::CritterObject*>(_vm->dataStack()->popObject());
    if (!critter)
    {
        _error("poison - WHO is not critter");
    }
    critter->setPoisonLevel(critter->poisonLevel() + amount);
}

}
