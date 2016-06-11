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

// Related headers
#include "../../VM/Handler/Opcode80BAHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BA::Opcode80BA(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80BA::_run()
            {
                Logger::debug("SCRIPT") << "[80BA] [+] int obj_is_carrying_obj_pid(GameObject* object, int PID)" << std::endl;
                auto PID = _script->dataStack()->popInteger();
                auto object = _script->dataStack()->popObject();

                int amount = 0;
                auto critter = dynamic_cast<Game::CritterObject*>(object);
                auto container = dynamic_cast<Game::ContainerItemObject*>(object);
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
                _script->dataStack()->push(amount);
            }
        }
    }
}
