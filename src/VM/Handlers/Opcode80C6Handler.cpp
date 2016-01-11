/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../../VM/Handlers/Opcode80C6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80C6Handler::Opcode80C6Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80C6Handler::_run()
{
    auto& debug = Logger::debug("SCRIPT");
    debug << "[80C6] [+] GVAR[num] = value" << std::endl;
    auto value = _vm->dataStack()->popInteger();
    auto num = _vm->dataStack()->popInteger();
    auto game = Game::getInstance();
    game->setGVAR(num, value);
    debug << "    num = " << num << ", value = " << value << std::endl;
}

}


