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
#include "../../Game/ContainerItemObject.h"
#include "../../VM/Handlers/Opcode80BAHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80BAHandler::Opcode80BAHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80BAHandler::_run()
{
    auto PID = _vm->popDataInteger();
    auto pointer = static_cast<Game::GameObject*>(_vm->popDataObject());

    int amount = 0;
    auto critter = dynamic_cast<Game::GameCritterObject*>(pointer);
    auto container = dynamic_cast<Game::GameContainerItemObject*>(pointer);
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

    Logger::debug("SCRIPT") << "[80BA] [+] int obj_is_carrying_obj_pid(GameObject* object, int PID)" << std::endl;
}

}
