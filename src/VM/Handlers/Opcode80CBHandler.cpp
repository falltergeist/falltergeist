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
#include "../../VM/Handlers/Opcode80CBHandler.h"
#include "../../VM/VM.h"
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Exception.h"
#include "../../Game/GameCritterObject.h"
#include "../../Game/GameDudeObject.h"

// Third party includes

namespace Falltergeist
{

Opcode80CBHandler::Opcode80CBHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80CBHandler::_run()
{
    int value = _vm->popDataInteger();
    int number = _vm->popDataInteger();
    if (number > 6) throw Exception("VM::opcode80CB - number out of range:" + std::to_string(number));
    auto object = std::static_pointer_cast<GameCritterObject>(_vm->popDataPointer());
    if (!object) throw Exception("VM::opcode80CB pointer error");
    object->setStat(number, value);
    if (std::dynamic_pointer_cast<GameDudeObject>(object))
    {
        _vm->pushDataInteger(3); // for dude
    }
    else
    {
        _vm->pushDataInteger(-1); // for critter
    }
    CrossPlatform::debug("[+] int set_critter_stat(GameCritterObject* who, int number, int value)", DEBUG_SCRIPT);
}

}
