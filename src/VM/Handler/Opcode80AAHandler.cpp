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
#include "../../VM/Handler/Opcode80AAHandler.h"

// C++ standard includes

// Falltergeist includes
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
            Opcode80AA::Opcode80AA(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80AA::_run()
            {
                auto &debug = Logger::debug("SCRIPT");
                debug << "[80AA] [+] int get_skill_value(GameCritterObject* who, int skill) " << std::endl;
                int skill = _script->dataStack()->popInteger();
                debug << "    skill = " << skill << std::endl;
                if (skill > 17 || skill < 0)
                {
                    _error("get_skill_value - skill out of range: " + std::to_string(skill));
                }
                auto object = _script->dataStack()->popObject();
                int value = 0;
                if (auto critter = dynamic_cast<Game::CritterObject*>(object))
                {
                    value = critter->skillValue((SKILL)skill);
                    _script->dataStack()->push(value);
                }
                else
                {
                    _error("get_skill_value(who, skill): who is not critter");
                }
            }
        }
    }
}


