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
#include "../../VM/Handler/Opcode80A1Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"
#include "../../VM/IFalloutStack.h
#include "VM/IFalloutValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode80A1::Opcode80A1(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode80A1::_run() {
                applyTo(_script);
            }

            int Opcode80A1::number() {
                return 0x80A1;
            }

            std::string Opcode80A1::name() {
                return "void give_exp_points(int points)";
            }

            std::string Opcode80A1::notes() {
                return "implemented";
            }

            void Opcode80A1::applyTo(std::shared_ptr<Falltergeist::VM::IFalloutContext> context) {
                auto points = context->dataStack()->pop()->asInteger();
                context->player()->setExperience(context->player()->experience() + points);
            }
        }
    }
}
