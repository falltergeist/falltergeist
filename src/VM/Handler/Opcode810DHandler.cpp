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
#include "../../VM/Handler/Opcode810DHandler.h"

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../../Game/CritterObject.h"
#include "../../Game/ItemObject.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810D::Opcode810D(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode810D::_run()
            {
                Logger::debug("SCRIPT") << "[810D] [=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
                const int pid = _script->dataStack()->popInteger();
                auto who = _script->dataStack()->popObject();
                if (auto critter = dynamic_cast<Game::CritterObject*>((Game::Object*)who))
                {
                    auto iterator = std::find_if(critter->inventory()->begin(), critter->inventory()->end(),
                                                [&] (Game::ItemObject * &item) { return item->PID() == pid; });
                    const bool found = iterator != critter->inventory()->end();
                    _script->dataStack()->push(found ? *iterator : nullptr);
                }
                else
                {
                    _warning(std::string("obj_carrying_pid_obj: 'who' is not valid GameCritterObject. It is ") + typeid(who).name());
                    _script->dataStack()->push(nullptr);
                }
            }
        }
    }
}
