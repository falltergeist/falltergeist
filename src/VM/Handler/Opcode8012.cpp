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
#include "../../VM/Handler/Opcode8012.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutStackValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8012::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto number = context->dataStack()->pop()->asInteger();
                auto value = context->dataStack()->at(context->dataStack()->stackBase() + number);
                context->dataStack()->push(value);

//                auto &debug = Logger::debug("SCRIPT");
//
//                debug << "[8012] [*] value = op_fetch_global[num]" << std::endl
//                      << "      num: " << number << std::endl;
//                //<< "     type: " << value.typeName() << std::endl
//                //<< "    value: " << value.toString();
//
//                debug << std::endl;
            }

            int Opcode8012::number() {
                return 0x8012;
            }

            std::string Opcode8012::name() {
                return "mixed op_fetch_global(int number)";
            }

            std::string Opcode8012::notes() {
                return "";
            }
        }
    }
}
