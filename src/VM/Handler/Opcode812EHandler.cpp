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

// Related headers
#include "../../VM/Handler/Opcode812EHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DoorSceneryObject.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode812E::Opcode812E(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode812E::_run()
            {
                auto &debug = Logger::debug("SCRIPT") << "[812E] [+] void obj_lock(GameObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (object)
                {
                    debug << "    PID: 0x" << std::hex << (object ? object->PID() : 0) << std::endl;
                    if (auto door = dynamic_cast<Game::DoorSceneryObject*>(object))
                    {
                        door->setLocked(true);
                    }
                    else if (auto container = dynamic_cast<Game::ContainerItemObject*>(object))
                    {
                        container->setLocked(true);
                    }
                    else
                    {
                        _warning("obj_lock: object is not door or container");
                    }
                }
                else
                {
                    _warning("obj_lock: object is null");
                }
            }
        }
    }
}
