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
#include "../../VM/Handler/Opcode80CFHandler.h"

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
            Opcode80CF::Opcode80CF(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80CF::_run()
            {
                Logger::debug("SCRIPT") << "[80CF] [=] int tile_in_tile_rect(int tile1, int tile2, int tile3, int tile4, int tile)" << std::endl;
                int targetHex = _script->dataStack()->popInteger();
                int bottomRight = _script->dataStack()->popInteger();
                /*int bottomLeft = */_script->dataStack()->popInteger();
                /*int upperRight = */_script->dataStack()->popInteger();
                int upperLeft = _script->dataStack()->popInteger();

                // That's how original engine does this:
                int targetX = targetHex % 200;
                int targetY = targetHex / 200;

                int upperLeftX = upperLeft % 200;
                int upperLeftY = upperLeft / 200;

                int bottomRightX = bottomRight % 200;
                int bottomRightY = bottomRight / 200;

                bool in = (targetX <= upperLeftX && targetY >= upperLeftY && targetX >= bottomRightX && targetY <= bottomRightY);
                _script->dataStack()->push(in);
            }
        }
    }
}


