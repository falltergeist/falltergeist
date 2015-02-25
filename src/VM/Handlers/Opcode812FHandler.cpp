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
#include "../../Game/DoorSceneryObject.h"
#include "../../Game/ContainerItemObject.h"
#include "../../VM/Handlers/Opcode812FHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode812FHandler::Opcode812FHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode812FHandler::_run()
{
<<<<<<< HEAD
    Logger::debug("SCRIPT") << "[812F] [+] void obj_unlock(GameObject* object)" << std::endl;
    auto object = _vm->dataStack()->popObject();
    if (object)
    {
        if (auto door = dynamic_cast<Game::GameDoorSceneryObject*>(object)) 
        {
            door->setLocked(false);
        }
        else if (auto container = dynamic_cast<Game::GameContainerItemObject*>(object)) 
        {
            container->setLocked(false);
        }
        else
        {
            _warning("obj_unlock: object is not door or container");
        }
    }
    else
    {
        _warning("obj_unlock: object is null");
    }
=======
    Logger::debug("SCRIPT") << "[812F] [+] void unlock(GameDoorSceneryObject* object)" << std::endl;
    auto object = static_cast<Game::GameDoorSceneryObject*>(_vm->popDataObject());
    object->setLocked(false);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
}

}


