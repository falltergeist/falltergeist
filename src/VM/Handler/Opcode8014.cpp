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
#include "../../VM/Handler/Opcode8014.h"

// C++ standard includes

// Falltergeist includes
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutStackValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8014::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto &debug = Logger::debug("SCRIPT");
                debug << "[8014] [+] value = op_fetch_external(name)" << std::endl;
                auto game = Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                std::string name;
                auto nameValue = _script->dataStack()->pop();
                switch (nameValue->type()) {
                    case IFalloutStackValue::Type::INTEGER:
                        name = _script->script()->identifiers().at((unsigned int) nameValue->asInteger());
                        break;
                    case IFalloutStackValue::Type::STRING: {
                        name = nameValue->asString();
                        break;
                    }
                    default:
                        _error(std::string("op_fetch_external - invalid argument type: ")); // + nameValue.typeName());
                }
                debug << " name = " << name;
                if (EVARS->find(name) == EVARS->end()) {
                    _error(std::string() + "op_fetch_external: exported variable \"" + name + "\" not found.");
                }
                auto value = EVARS->at(name);
                //debug << ", type = " << value.typeName() << ", value = " << value.toString() << std::endl;
                _script->dataStack()->push(value);
            }

            int Opcode8014::number() {
                return 0x8014;
            }

            std::string Opcode8014::name() {
                return "mixed op_fetch_external(int|string name)";
            }

            std::string Opcode8014::notes() {
                return "";
            }
        }
    }
}
