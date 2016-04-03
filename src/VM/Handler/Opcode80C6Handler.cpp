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
#include "../../VM/Handler/Opcode80C6Handler.h"

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
            Opcode80C6::Opcode80C6(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80C6::_run()
            {
                auto& debug = Logger::debug("SCRIPT");
                debug << "[80C6] [+] GVAR[num] = value" << std::endl;
                auto value = _script->dataStack()->popInteger();
                auto num = _script->dataStack()->popInteger();
                auto game = Game::getInstance();
                game->setGVAR(num, value);
                debug << "    num = " << num << ", value = " << value << std::endl;
            }
        }
    }
}


