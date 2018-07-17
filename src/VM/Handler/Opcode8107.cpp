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
#include "Opcode8107.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Object.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            void Opcode8107::applyTo(std::shared_ptr<IFalloutContext> context) {
                auto object = context->dataStack()->pop()->asObject();
                auto level = context->dataStack()->pop()->asInteger();
                auto radius = context->dataStack()->pop()->asInteger();
                if (level > 100 || level < 0) {
                    // TODO
                    //_warning("obj_set_light_level: level should be 0-100");
                    return;
                }
                if (radius > 8 || radius < 0) {
                    // TODO
                    //_warning("obj_set_light_level: radius should be 0-8");
                    return;
                }

                unsigned int light = 65536 / 100 * level;
                object->setLightIntensity(light);
                object->setLightRadius(radius);
            }

            int Opcode8107::number() {
                return 0x8107;
            }

            std::string Opcode8107::name() {
                return "void obj_set_light_level(Object* object, int level, int radius)";
            }

            std::string Opcode8107::notes() {
                return "";
            }
        }
    }
}
