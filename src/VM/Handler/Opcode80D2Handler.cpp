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
#include "../../VM/Handler/Opcode80D2Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D2::Opcode80D2(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80D2::_run()
            {
                Logger::debug("SCRIPT") << "[80D2] [=] int tile_distance(int tile1, int tile2)" << std::endl;
                auto tile1 = _script->dataStack()->popInteger();
                auto tile2 = _script->dataStack()->popInteger();
                if (tile1 < 0 || tile1 >= 200*200 || tile2 < 0 || tile2 >= 200*200)
                {
                    _script->dataStack()->push(9999);
                }
                else
                {
                    auto grid = Game::getInstance()->locationState()->hexagonGrid();
                    auto dist = grid->distance(grid->at(tile1), grid->at(tile2));
                    _script->dataStack()->push(dist);
                }
            }
        }
    }
}
