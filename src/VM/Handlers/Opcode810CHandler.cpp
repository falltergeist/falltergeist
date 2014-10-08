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

// C++ standard includes

// Falltergeist includes
#include "../../Engine/Exception.h"
#include "../../Engine/Logger.h"
#include "../../Game/GameObject.h"
#include "../../VM/Handlers/Opcode810CHandler.h"
#include "../../VM/VM.h"


// Third party includes

namespace Falltergeist
{

Opcode810CHandler::Opcode810CHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode810CHandler::_run()
{
    auto& debug = Logger::debug("SCRIPT");
    debug << "[810C] [*] void anim(void* who, int anim, int direction)" << std::endl;

    int direction;
    switch (_vm->dataStack()->top()->type())
    {
        case VMStackValue::TYPE_INTEGER:
        {
            direction = _vm->popDataInteger();
            break;
        }
        case VMStackValue::TYPE_POINTER:
        {
            auto object = static_cast<GameObject*>(_vm->popDataPointer());
            direction = object->orientation();
            break;
        }
        default:
        {
            throw Exception("Opcode810CHandler - wrong direction type");
        }
    }
    auto anim = _vm->popDataInteger();
    auto who = _vm->popDataPointer();
    //_anim(who, anim, direction);

    debug << "    direction = " << std::hex << direction << std::endl;
    debug << "    anim = " << std::hex << anim << std::endl;
    debug << "    who = " << who << std::endl;
}

}
