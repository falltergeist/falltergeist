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
#include "../../VM/Handler/Opcode8027Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8027::Opcode8027(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8027::_run()
            {
                Logger::debug("SCRIPT") << "[8027] [?] op_check_arg_count" << std::endl;
                _script->dataStack()->pop(); // number of actual arguments
                _script->dataStack()->pop(); // procedure index
                // @TODO: compare number of arguments with procedure info and throw script exception if they are not equal
            }
        }
    }
}
