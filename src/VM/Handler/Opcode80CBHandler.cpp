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
#include "../../VM/Handler/Opcode80CBHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/CritterObject.h"
#include "../../Game/DudeObject.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CB::Opcode80CB(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80CB::_run()
            {
                Logger::debug("SCRIPT") << "[80CB] [+] int set_critter_stat(GameCritterObject* who, int number, int value)" << std::endl;
                int value = _script->dataStack()->popInteger();
                int number = _script->dataStack()->popInteger();
                if (number > 6)
                {
                    _error("set_critter_stat - number out of range:" + std::to_string(number));
                }
                auto object = _script->dataStack()->popObject();
                if (!object)
                {
                    _error("set_critter_stat(who, num, value) - who is null");
                }
                auto critter = dynamic_cast<Game::CritterObject*>(object);
                if (!critter)
                {
                    _error("set_critter_stat(who, num, value) - who is not a critter");
                }
                critter->setStat((STAT)number, value);
                if (dynamic_cast<Game::DudeObject*>(critter))
                {
                    _script->dataStack()->push(3); // for dude
                }
                else
                {
                    _script->dataStack()->push(-1); // for critter
                }
            }
        }
    }
}
