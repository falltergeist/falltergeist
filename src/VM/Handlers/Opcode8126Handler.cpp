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
#include "../../VM/Handlers/Opcode8126Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode8126Handler::Opcode8126Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8126Handler::_run()
{
    Logger::debug("SCRIPT") << "[8126] [-] void reg_anim_animate_forever(GameObject* obj , int delay)" << std::endl;
    int delay = _vm->popDataInteger();
    /*
    // delay - must be -1
    if (delay != -1)
    {
        throw Exception("Opcode8126Handler - delay must be -1");
    }
    */
    auto object = static_cast<Game::GameObject*>(_vm->popDataPointer());
    auto queue = dynamic_cast<AnimationQueue*>(object->ui());
    if (queue)
    {
        queue->stop();
        queue->setRepeat(true); // forever
        queue->start();
    }
}

}
