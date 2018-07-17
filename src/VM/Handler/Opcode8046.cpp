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
#include "Opcode8046.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8046::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto value = context->dataStack()->pop();
                if (value->type() == IFalloutValue::Type::INTEGER) {
                    context->dataStack()->push(-value->asInteger());
                } else if (value->type() == IFalloutValue::Type::FLOAT) {
                    context->dataStack()->push(-value.asFloat());
                } else {
                    // TODO throw exception
                    //_error(std::string("Invalid argument type: ") + value.typeName());
                }
            }


            int Opcode8046::number() {
                return 0x8046;
            }

            std::string Opcode8046::name() {
                return "op_negate(value)";
            }

            std::string Opcode8046::notes() {
                return "";
            }
        }
    }
}
