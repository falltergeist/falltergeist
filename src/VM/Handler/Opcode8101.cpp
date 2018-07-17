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
#include "Opcode8101.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/IFalloutStack.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8101::applyTo(std::shared_ptr<IFalloutContext> context) {
                context->dataStack()->push(Game::getInstance()->locationState()->currentMapIndex());
            }
            
            int Opcode8101::number() {
                return 0x8101;
            }

            std::string Opcode8101::name() {
                return "int cur_map_index(void)";
            }

            std::string Opcode8101::notes() {
                return "";
            }
        }
    }
}
