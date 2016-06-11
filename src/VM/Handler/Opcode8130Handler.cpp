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
#include "../../VM/Handler/Opcode8130Handler.h"

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
            Opcode8130::Opcode8130(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8130::_run()
            {
                Logger::debug("SCRIPT") << "[8130] [+] int obj_is_open(GameObject* object) " << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object)
                {
                    _error("obj_is_open: object is NULL");
                }
                // @TODO: need some refactoring to get rid of this ugly if-elses
                if (auto door = dynamic_cast<Game::DoorSceneryObject*>(object))
                {
                    _script->dataStack()->push(door->opened());
                }
                else if (auto container = dynamic_cast<Game::ContainerItemObject*>(object))
                {
                    _script->dataStack()->push(container->opened());
                }
                else
                {
                    _error("obj_is_open: object is not openable type!");
                }
            }
        }
    }
}


