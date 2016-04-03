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
#include "../../VM/Handler/Opcode80C2Handler.h"

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
            Opcode80C2::Opcode80C2(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80C2::_run()
            {
                Logger::debug("SCRIPT") << "[80C2] [*] LVAR[num] = value" << std::endl;
                auto value = _script->dataStack()->pop();
                unsigned int num = _script->dataStack()->popInteger();
                while (num >= _script->LVARS()->size())
                {
                    _script->LVARS()->push_back(StackValue(0));
                }
                _script->LVARS()->at(num) = value;
            }
        }
    }
}


