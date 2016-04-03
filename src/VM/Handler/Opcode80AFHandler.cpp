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
#include "../../VM/Handler/Opcode80AFHandler.h"

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
            Opcode80AF::Opcode80AF(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80AF::_run()
            {
                Logger::debug("SCRIPT") << "[80AF] [*] int is_success(int val)" << std::endl;
                auto value = _script->dataStack()->popInteger();
                switch(value)
                {
                    case 0:
                    case 1:
                        _script->dataStack()->push(0);
                        break;
                    case 2:
                    case 3:
                        _script->dataStack()->push(1);
                        break;
                    default:
                        _error("is_success - wrong argument: " + std::to_string(value));
                        break;
                }
            }
        }
    }
}


