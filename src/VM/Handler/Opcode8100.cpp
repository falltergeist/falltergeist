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
#include "Opcode8100.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8100::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto object = context->dataStack()->pop()->asObject();
                if (!object) {
                    context->dataStack()->push(0);
                } else {
                    context->dataStack()->push(object->PID());
                }
            }

            int Opcode8100::number() {
                return 0x8100;
            }

            std::string Opcode8100::name() {
                return "in obj_pid(void* obj)";
            }

            std::string Opcode8100::notes() {
                return "";
            }
        }
    }
}


