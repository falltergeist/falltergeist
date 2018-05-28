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
#include "../../VM/Handler/Opcode8028Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Format/Int/File.h"
#include "../../Format/Int/Procedure.h"
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../VM/IFalloutProcedure.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutStackValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8028::Opcode8028(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8028::applyTo(std::shared_ptr<IFalloutContext> context) {
                Logger::debug("SCRIPT") << "[8028] [?] int lookup_string_proc(string)" << std::endl;
                std::string name = context->dataStack()->pop()->asString();
                context->dataStack()->push((int)context->procedure(name)->bodyOffset());
            }

            void Opcode8028::_run() {
                applyTo(_script);
            }
        }
    }
}
