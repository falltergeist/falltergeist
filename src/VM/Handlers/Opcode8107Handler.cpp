/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Falltergeist includes
#include <Game/Object.h>
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode8107Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8107Handler::Opcode8107Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8107Handler::_run()
{
    Logger::debug("SCRIPT") << "[8107] [*] void obj_set_light_level(Object* object, int level, int radius)" << std::endl;
    auto object = _vm->dataStack()->popObject();
    auto level = _vm->dataStack()->popInteger();
    auto radius = _vm->dataStack()->popInteger();
    if (level > 100 || level < 0)
    {
        _warning("obj_set_light_level: level should be 0-100");
        return;
    }
    if (radius > 8 || radius < 0)
    {
        _warning("obj_set_light_level: radius should be 0-8");
        return;
    }

    unsigned int light = 65536/100*level;
    object->setLightIntensity(light);
    object->setLightRadius(radius);
}

}