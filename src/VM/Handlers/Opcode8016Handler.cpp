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
#include "../../Game.h"
#include "../../Logger.h"
#include "../../States/LocationState.h"
#include "../../VM/Handlers/Opcode8016Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8016Handler::Opcode8016Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8016Handler::_run()
{
    auto name = *static_cast<std::string*>(_vm->popDataPointer());
    auto EVARS = Game::getInstance()->locationState()->EVARS();
    if (EVARS->find(name) == EVARS->end())
    {
        EVARS->insert(std::make_pair(name, nullptr));
    }
    Logger::debug("SCRIPT") << "[8016] [*] export(name)" << std::endl
                            << "    name: " << name << std::endl;
}

}
