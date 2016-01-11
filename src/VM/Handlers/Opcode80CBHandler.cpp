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
#include "../../Game/CritterObject.h"
#include "../../Game/DudeObject.h"
#include "../../VM/Handlers/Opcode80CBHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80CBHandler::Opcode80CBHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80CBHandler::_run()
{
    Logger::debug("SCRIPT") << "[80CB] [+] int set_critter_stat(GameCritterObject* who, int number, int value)" << std::endl;
    int value = _vm->dataStack()->popInteger();
    int number = _vm->dataStack()->popInteger();
    if (number > 6)
    {
        _error("set_critter_stat - number out of range:" + std::to_string(number));
    }
    auto object = _vm->dataStack()->popObject();
    if (!object) 
    {
        _error("set_critter_stat(who, num, value) - who is null");
    }
    auto critter = dynamic_cast<Game::CritterObject*>(object);
    if (!critter)
    {
        _error("set_critter_stat(who, num, value) - who is not a critter");
    }
    critter->setStat((STAT)number, value);
    if (dynamic_cast<Game::DudeObject*>(critter))
    {
        _vm->dataStack()->push(3); // for dude
    }
    else
    {
        _vm->dataStack()->push(-1); // for critter
    }
}

}
