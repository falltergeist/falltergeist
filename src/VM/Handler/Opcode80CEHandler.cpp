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
#include "../../VM/Handler/Opcode80CEHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/CritterObject.h"
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
            Opcode80CE::Opcode80CE(VM::Script* script) : OpcodeHandler(script)
            {
            }

            // TODO: handle ANIMATE_INTERRUPT
            void Opcode80CE::_run()
            {
                Logger::debug("SCRIPT") << "[80CE] [=] void animate_move_obj_to_tile(void* who, int tile, int speed)" << std::endl;
                int speed = _script->dataStack()->popInteger();
                int tile = _script->dataStack()->popInteger();
                auto object = _script->dataStack()->popObject();

                // ANIMATE_WALK      (0)
                // ANIMATE_RUN       (1)
                // ANIMATE_INTERRUPT (16) - flag to interrupt current animation
                auto critter = dynamic_cast<Game::CritterObject*>(object);
                auto state = Game::Game::getInstance()->locationState();
                if (state)
                {
                    auto tileObj = state->hexagonGrid()->at(tile);
                    auto path = state->hexagonGrid()->findPath(object->hexagon(), tileObj);
                    if (path.size())
                    {
                        critter->stopMovement();
                        critter->setRunning((speed & 1) != 0);
                        auto queue = critter->movementQueue();
                        for (auto pathHexagon : path)
                        {
                            queue->push_back(pathHexagon);
                        }
                    }
                }
            }
        }
    }
}
