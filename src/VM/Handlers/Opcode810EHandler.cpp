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
#include "../../Graphics/AnimationQueue.h"
#include "../../Logger.h"
#include "../../Game/Object.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Handlers/Opcode810EHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode810EHandler::Opcode810EHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode810EHandler::_run()
{
    Logger::debug("SCRIPT") << "[810E] [=] void reg_anim_func(int mode, int arg)" << std::endl;
    auto arg = _vm->dataStack()->pop(); // pointer or integer
    auto p1 = _vm->dataStack()->popInteger();
    switch (p1)
    {
        case 0x1: // ANIM_BEGIN
        {
            // @TODO: implement
            // auto arg = popDataInteger();
            // RB_UNRESERVED (1) - незарезервированная последовательность, может не воспроизвестись, если отсутствуют свободные слоты
            // RB_RESERVED (2) - зарезервированная последовательность, должна воспроизвестись в любом случае
            break;
        }
        case 0x2: // ANIM_CLEAR
        {
            auto object = arg.objectValue();
            if (auto critterObject = dynamic_cast<Game::GameCritterObject*>(object))
            {
                critterObject->stopMovement();
            }
            else
            {
                auto queue = dynamic_cast<AnimationQueue*>(object->ui());
                if (queue) queue->stop();
            }
            break;
        }
        case 0x3: // ANIMATION_END
        {
            // @TODO: implement
            break;
        }
        default:
        {
            throw Exception("Opcode810EHandler - unsupported mode");
        }
    }

}

}
