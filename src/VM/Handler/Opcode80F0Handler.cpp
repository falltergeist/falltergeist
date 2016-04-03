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
#include "../../VM/Handler/Opcode80F0Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F0::Opcode80F0(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80F0::_run()
            {
                Logger::debug("SCRIPT") << "[80F0] [=] void add_timer_event(void* obj, int time, int info)" << std::endl;
                int fixedParam = _script->dataStack()->popInteger();
                int delay = _script->dataStack()->popInteger();
                Game::Object* object = _script->dataStack()->popObject();
                auto state = Game::Game::getInstance()->locationState();
                if (state)
                {
                    state->addTimerEvent(object, delay, fixedParam);
                }
            }
        }
    }
}
