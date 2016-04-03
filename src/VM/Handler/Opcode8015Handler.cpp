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
#include "../../VM/Handler/Opcode8015Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8015::Opcode8015(VM::Script *script) : OpcodeHandler(script)
            {
            }

            void Opcode8015::_run()
            {
                Logger::debug("SCRIPT") << "[8015] [*] op_store_external(name, value)" << std::endl;
                std::string name = _script->dataStack()->popString();
                auto value = _script->dataStack()->pop();
                auto game = Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                (*EVARS)[name] = value;
            }
        }
    }
}
