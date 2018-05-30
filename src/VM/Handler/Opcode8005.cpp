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
#include "../../VM/Handler/Opcode8005.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutProcedure.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutStackValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8005::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto functionIndex = context->dataStack()->pop()->asInteger();
                // @TODO: pass arguments and call external procedures
                /*auto argumentCount = _script->dataStack()->popInteger();
                std::vector<int> args;
                for (int i = 0; i < argumentCount; i++)
                {
                    args.push_back(_script->dataStack()->popInteger());
                }*/
                context->setProgramCounter(context->procedure(functionIndex)->bodyOffset());
            }

            int Opcode8005::number()
            {
                return 0x8005;
            }

            std::string Opcode8005::name()
            {
                return "void op_call(int index)";
            }

            std::string Opcode8005::notes()
            {
                return "Partially implemented";
            }
        }
    }
}
