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
#include "../../VM/Handler/Opcode80A7Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Game/Object.h"
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
            Opcode80A7::Opcode80A7(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80A7::_run()
            {
                Logger::debug("SCRIPT") << "[80A7] [+] GameObject* tile_contains_pid_obj(int position, int elevation, int PID)" << std::endl;
                auto PID = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto game = Game::getInstance();
                Game::Object* found = nullptr;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects())
                {
                    if (object->PID() == PID && object->elevation() == elevation)
                    {
                        found = object;
                        break;
                    }
                }
                _script->dataStack()->push(found);
            }
        }
    }
}


