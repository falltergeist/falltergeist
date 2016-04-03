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
#include "../../VM/Handler/Opcode80D8Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
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
            Opcode80D8::Opcode80D8(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80D8::_run()
            {
                Logger::debug("SCRIPT") << "[80D8] [=] void add_obj_to_inven(void* who, void* item)" << std::endl;
                auto item = dynamic_cast<Game::ItemObject*>(_script->dataStack()->popObject());
                auto invenObj = _script->dataStack()->popObject();

                if (!item)
                {
                    _error("add_obj_to_inven - item not instanceof GameItemObject");
                    return;
                }

                std::vector<Game::ItemObject*>* inven;
                if (auto critterObj = dynamic_cast<Game::CritterObject*>(invenObj))
                {
                    inven = critterObj->inventory();
                }
                else if (auto contObj = dynamic_cast<Game::ContainerItemObject*>(invenObj))
                {
                    inven = contObj->inventory();
                }
                else
                {
                    _error("add_obj_to_inven - wrong WHO parameter");
                    return;
                }

                inven->push_back(item);

                if (item->hexagon())
                {
                    auto location = Game::Game::getInstance()->locationState();
                    if (location)
                    {
                        location->moveObjectToHexagon(item, nullptr);
                    }
                }
            }
        }
    }
}
