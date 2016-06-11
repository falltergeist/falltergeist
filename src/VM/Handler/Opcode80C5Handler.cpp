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
#include "../../VM/Handler/Opcode80C5Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C5::Opcode80C5(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80C5::_run()
            {
                auto& debug = Logger::debug("SCRIPT");
                debug << "[80C5] [?] GVAR[num]" << std::endl;
                int num = _script->dataStack()->popInteger();
                int value;
                if (num < 0)
                {
                    value = 0;
                }
                else
                {
                    auto game = Game::getInstance();
                    value = game->GVAR(num);
                }
                _script->dataStack()->push(value);

                debug << "    num = 0x" << std::hex << num << std::endl;
                debug << "    value = 0x" << std::hex << value << std::endl;
            }
        }
    }
}


