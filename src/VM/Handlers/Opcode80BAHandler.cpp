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
    Logger::debug("SCRIPT") << "[80BA] [+] int obj_is_carrying_obj_pid(GameObject* object, int PID)" << std::endl;
    auto PID = _vm->dataStack()->popInteger();
    auto object = _vm->dataStack()->popObject();

    int amount = 0;
    auto critter = dynamic_cast<Game::GameCritterObject*>(object);
    auto container = dynamic_cast<Game::GameContainerItemObject*>(object);
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
        _error("obj_is_carrying_obj_pid - invalid object type");
    }
    _vm->dataStack()->push(amount);
}

}
