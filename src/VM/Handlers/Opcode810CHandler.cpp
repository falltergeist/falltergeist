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
#include "../../Exception.h"
#include "../../Logger.h"
#include "../../Game/GameCritterObject.h"
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
    int direction = _vm->popDataInteger();
    int animation = _vm->popDataInteger();
    auto critter = static_cast<GameCritterObject*>(_vm->popDataPointer());

    Logger::debug("SCRIPT") << "[810C] [*] void anim(GameCritterObject* who, int animation, int direction)" << std::endl
                            << "    direction = 0x" << std::hex << direction << std::endl
                            << "    animation = 0x" << std::hex << animation << std::endl;
    switch (animation)
    {
        case 1000: // ANIMATE_ROTATION
        {
            critter->setActionAnimation("aa");
            break;
        }
        default:
            throw Exception("Opcode810C - unimplemented animation: " + std::to_string(animation));
            break;
    }
}

}
