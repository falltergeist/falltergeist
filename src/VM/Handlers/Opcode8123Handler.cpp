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
#include "../../VM/Handlers/Opcode8123Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8123Handler::Opcode8123Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8123Handler::_run()
{
    auto critter = dynamic_cast<Game::CritterObject*>(_vm->dataStack()->popObject());
    auto value = critter->poisonLevel();
    _vm->dataStack()->push(value);
    Logger::debug("SCRIPT") << "[8123] [+] int value = GetPoison(GameCritterObject* critter)" << std::endl
                            << "    value = " << value << std::endl;
}

}
