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
#include "../../VM/Handler/Opcode8004.h"

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutStackValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8004::Opcode8004(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8004::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto address = context->dataStack()->pop()->asInteger();
                Logger::debug("SCRIPT")
                    << "[8004] [*] op_jmp(address)" << std::endl
                    << "    address: " << std::hex << address << std::endl;
                context->setProgramCounter(address);
            }

            void Opcode8004::_run() {
                applyTo(_script);
            }
        }
    }
}
