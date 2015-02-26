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
#include "../../VM/Handlers/Opcode812EHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode812EHandler::Opcode812EHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode812EHandler::_run()
{
    auto &debug = Logger::debug("SCRIPT") << "[812E] [+] void obj_lock(GameDoorSceneryObject* object)" << std::endl;
    auto object = _vm->dataStack()->popObject();
    if (object)
    {
        debug << "    PID: 0x" << std::hex << (object ? object->PID() : 0) << std::endl;
        if (auto door = dynamic_cast<Game::GameDoorSceneryObject*>(object)) 
        {
            door->setLocked(true);
        }
        else
        {
            Logger::warning("SCRIPT") << "Opcode812EHandler: object is not door" << std::endl;
        }
    }
    else
    {
        Logger::warning("SCRIPT") << "Opcode812EHandler: object is null" << std::endl;
    }
}

}


