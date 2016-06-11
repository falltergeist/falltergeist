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
#include "../../VM/Handler/Opcode802FHandler.h"

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
            Opcode802F::Opcode802F(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode802F::_run()
            {
                auto condition = _script->dataStack()->popLogical();
                auto address = _script->dataStack()->popInteger();
                Logger::debug("SCRIPT") << "[802F] [*] op_if(address, condition) " << std::hex << _script->programCounter() << std::endl
                                        << "    address = " << std::hex << address << std::endl
                                        << "    condition = " << std::dec << condition << std::endl;
                if (!condition)
                {
                    _script->setProgramCounter(address);
                }
            }
        }
    }
}
