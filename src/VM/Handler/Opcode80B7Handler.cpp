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
#include "../../VM/Handler/Opcode80B7Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/ObjectFactory.h"
#include "../../Logger.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B7::Opcode80B7(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80B7::_run()
            {
                Logger::debug("SCRIPT") << "[80B7] [+] GameObject* create_object_sid(int PID, int position, int elevation, int SID)" << std::endl;
                auto SID = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto PID = _script->dataStack()->popInteger();
                auto object = Game::getInstance()->locationState()->addObject(PID, position, elevation);
                if (SID > 0)
                {
                    auto intFile = ResourceManager::getInstance()->intFileType(SID);
                    if (intFile)
                    {
                        object->setScript(new VM::Script(intFile, object));
                    }
                }
                if (object->script())
                {
                    object->script()->initialize();
                }
                _script->dataStack()->push(object);
            }
        }
    }
}
