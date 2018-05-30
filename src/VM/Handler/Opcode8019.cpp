/*
 * Copyright 2012-2018 Falltergeist Developers.
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
#include "../../VM/Handler/Opcode8019.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8019::applyTo(std::shared_ptr<IFalloutContext> context) {
                context->returnStack()->swap();
            }

            int Opcode8019::number() {
                return 0x8019;
            }
            
            std::string Opcode8019::name() {
                return "void op_swapa()";
            }
            
            std::string Opcode8019::notes() {
                return "";
            }
        }
    }
}
