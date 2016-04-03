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
#include "../../VM/Handler/Opcode80D5Handler.h"

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
            Opcode80D5::Opcode80D5(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80D5::_run()
            {
                Logger::debug("SCRIPT") << "[80D5] [*] int tile_num_in_direction(int start_tile, int dir, int distance)" << std::endl;
                auto distance = _script->dataStack()->popInteger();
                auto dir = _script->dataStack()->popInteger();
                auto start_tile = _script->dataStack()->popInteger();

                if (dir < 0 || dir > 5 || distance < 0)
                {
                    //error?
                    _script->dataStack()->push(start_tile);
                }
                else
                {
                    auto grid = Game::getInstance()->locationState()->hexagonGrid();
                    auto hex = grid->hexInDirection(grid->at(start_tile), dir, distance);
                    if (hex)
                    {
                        _script->dataStack()->push(hex->number());

                    }
                    else
                    {
                        _script->dataStack()->push(start_tile);
                    }
                }
            }
        }
    }
}
