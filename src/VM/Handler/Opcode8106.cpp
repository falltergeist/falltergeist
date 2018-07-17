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
#include "Opcode8106.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/ArmorItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"



// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8106::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto where = context->dataStack()->pop()->asInteger();
                auto critter = dynamic_cast<Game::CritterObject *>(context->dataStack()->pop()->asObject());
                switch (where) {
                    case 0: // ARMOR SLOT
                        context->dataStack()->push(critter->armorSlot());
                        break;
                    case 1: // RIGHT HAND SLOT
                        context->dataStack()->push(critter->rightHandSlot());
                        break;
                    case 2: // LEFT HAND SLOT
                        context->dataStack()->push(critter->leftHandSlot());
                        break;
                    case -2: // INVENTORY COUNT
                        context->dataStack()->push((unsigned int) critter->inventory()->size());
                        break;
                    default:
                        // TODO throw exception
                        //_error(std::string("critter_inven_obj - invalid slot: ") + std::to_string(where));
                        break;
                }
            }
            
            int Opcode8106::number() {
                return 0x8106;
            }

            std::string Opcode8106::name() {
                return "void* (int) critter_inven_obj(GameCritterObject* critter, int where)";
            }

            std::string Opcode8106::notes() {
                return "";
            }
        }
    }
}
