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
#include "../../VM/Handler/Opcode8137Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Logger.h"
#include "../../State/State.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8137::Opcode8137(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8137::_run()
            {
                int time = _script->dataStack()->popInteger(); // original engine ignores time
                Logger::debug("SCRIPT") << "[8137] [=] void gfade_in(int time)" << std::endl
                                        << "    time = " << time << std::endl;

                auto state = Game::getInstance()->topState();
                state->scriptFade(_script, true);
                throw HaltException();
            }
        }
    }
}
