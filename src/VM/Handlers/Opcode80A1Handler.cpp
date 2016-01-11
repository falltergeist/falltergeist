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
#include "../../VM/Handlers/Opcode80A1Handler.h"
#include "../../VM/VM.h"
#include "../../Game/Game.h"
#include "../../Game/DudeObject.h"

// Third party includes

namespace Falltergeist
{

Opcode80A1Handler::Opcode80A1Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80A1Handler::_run()
{
    Logger::debug("SCRIPT") << "[80A1] [+] void give_exp_points(int points)" << std::endl;
    auto points = _vm->dataStack()->popInteger();
    auto game = Game::getInstance();
    game->player()->setExperience(game->player()->experience() + points);
}

}


