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
#include "../../VM/Handler/Opcode8138Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8138::Opcode8138(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8138::_run()
            {
                //TODO: search ContainerItemObject and CritterObject inventories recursively if it has container itemobjects in it
                //for now recursive inventories are not yet implemented since ItemObject has no inventory vector
                
                Logger::debug("SCRIPT") << "[8138] [=] int item_caps_total(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (auto container = dynamic_cast<Game::ContainerItemObject*>(object))
                {
                    for(auto item: *container->inventory())
                    {   
                        if(item->PID() == 519)
                        {
                            _script->dataStack()->push(item->amount());
                            return;
                        }
                    }
                    _script->dataStack()->push(0);
                }
                else if (auto critter = dynamic_cast<Game::CritterObject*>(object))
                {
                    for(auto item: *critter->inventory())
                    {   
                        if(item->PID() == 519)
                        {
                            _script->dataStack()->push(item->amount());
                            return;
                        }
                    }
                    _script->dataStack()->push(0);
                }
                else
                {
                    _error("item_caps_total: object type has no inventory!");
                    _script->dataStack()->push(0);
                }
            }
        }
    }
}
