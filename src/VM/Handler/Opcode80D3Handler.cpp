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
#include "../../VM/Handler/Opcode80D3Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
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
            Opcode80D3::Opcode80D3(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80D3::_run()
            {
                Logger::debug("SCRIPT") << "[80D3] int tile_distance_objs(void* p2, void* p1)" << std::endl;
                auto obj1 = _script->dataStack()->popObject();
                auto obj2 = _script->dataStack()->popObject();
                int distance = Game::getInstance()->locationState()->hexagonGrid()->distance(obj1->hexagon(), obj2->hexagon());
                _script->dataStack()->push(distance);
            }
        }
    }
}
