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

// Related headers
#include "../../VM/Handler/Opcode8126Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../UI/AnimationQueue.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8126::Opcode8126(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8126::_run()
            {
                Logger::debug("SCRIPT") << "[8126] [-] void reg_anim_animate_forever(GameObject* obj , int delay)" << std::endl;
                /* int delay = */ (void)_script->dataStack()->popInteger();
                /*
                // delay - must be -1
                if (delay != -1)
                {
                    _error("Opcode8126Handler - delay must be -1");
                }
                */
                auto object = _script->dataStack()->popObject();
                auto queue = dynamic_cast<UI::AnimationQueue*>(object->ui());
                if (queue)
                {
                    queue->stop();
                    queue->setRepeat(true); // forever
                    queue->start();
                }
            }
        }
    }
}
