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
#include "../../VM/Handler/Opcode8102Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8102::Opcode8102(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8102::_run()
            {
                Logger::debug("SCRIPT") << "[8102] [*] int critter_add_trait(void* who, int trait_type, int trait, int amount) " << std::endl;
                /* auto amount = */ (void)_script->dataStack()->popInteger();
                /* auto trait = */ (void)_script->dataStack()->popInteger();
                /* auto trait_type = */ (void)_script->dataStack()->popInteger();
                /* auto who = */ (void)_script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}


