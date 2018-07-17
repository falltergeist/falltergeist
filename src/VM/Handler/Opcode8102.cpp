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
#include "Opcode8102.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8102::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto dataStack = context->dataStack();
                /* auto amount = */ (void) dataStack->pop()->asInteger();
                /* auto trait = */ (void) dataStack->pop()->asInteger();
                /* auto trait_type = */ (void) dataStack->pop()->asInteger();
                /* auto who = */ (void) dataStack->pop()->asObject();
                dataStack->push(0);
            }

            int Opcode8102::number() {
                return 0x8102;
            }

            std::string Opcode8102::name() {
                return "int critter_add_trait(void* who, int trait_type, int trait, int amount)";
            }

            std::string Opcode8102::notes() {
                return "";
            }
        }
    }
}


