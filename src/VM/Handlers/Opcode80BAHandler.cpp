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
#include <iostream>

// Falltergeist includes
#include "../../VM/Handlers/Opcode80BAHandler.h"
#include "../../VM/VM.h"
#include "../../Game/GameCritterObject.h"
#include "../../Game/GameContainerItemObject.h"
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{

Opcode80BAHandler::Opcode80BAHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80BAHandler::_run()
{
    auto PID = _vm->popDataInteger();
    auto pointer = std::static_pointer_cast<GameObject>(_vm->popDataPointer());

    int amount = 0;
    auto critter = std::dynamic_pointer_cast<GameCritterObject>(pointer);
    auto container = std::dynamic_pointer_cast<GameContainerItemObject>(pointer);
    if (critter)
    {
        for (auto object : *critter->inventory()) if (object->PID() == PID) amount += object->amount();
    }
    else if (container)
    {
        for (auto object : *container->inventory()) if (object->PID() == PID) amount += object->amount();
    }
    else
    {
        throw Exception("VM::opcode80ba - unknown object type");
    }
    _vm->pushDataInteger(amount);

    CrossPlatform::debug("[+] int obj_is_carrying_obj_pid(GameObject* object, int PID)", DEBUG_SCRIPT);

}

}
