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

// Related headerse
#include "../../VM/Handler/Opcode80FCHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80FC::Opcode80FC(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80FC::_run()
            {

                int amount = _script->dataStack()->popInteger();
                Logger::debug("SCRIPT") << "[80FC] [=] void game_time_advance(int amount)" << std::endl
                                        << "    amount = " << amount << std::endl;
                auto time = Game::getInstance()->gameTime();
                for (auto i = 0; i != amount; ++i)
                {
                    time->increaseTicks();
                }
            }
        }
    }
}
