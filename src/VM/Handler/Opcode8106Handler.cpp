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
#include "../../VM/Handler/Opcode8106Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/ArmorItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8106::Opcode8106(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8106::_run()
            {
                Logger::debug("SCRIPT") << "[8106] [=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)" << std::endl;
                auto where = _script->dataStack()->popInteger();
                auto critter = dynamic_cast<Game::CritterObject*>(_script->dataStack()->popObject());
                switch (where)
                {
                case 0: // ARMOR SLOT
                    _script->dataStack()->push(critter->armorSlot());
                    break;
                case 1: // RIGHT HAND SLOT
                    _script->dataStack()->push(critter->rightHandSlot());
                    break;
                case 2: // LEFT HAND SLOT
                    _script->dataStack()->push(critter->leftHandSlot());
                    break;
                case -2: // INVENTORY COUNT
                    _script->dataStack()->push((unsigned int)critter->inventory()->size());
                    break;
                default:
                    _error(std::string("critter_inven_obj - invalid slot: ") + std::to_string(where));
                }
            }
        }
    }
}
