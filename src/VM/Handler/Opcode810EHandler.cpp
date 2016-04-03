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
#include "../../VM/Handler/Opcode810EHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/CritterObject.h"
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
            Opcode810E::Opcode810E(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode810E::_run()
            {
                Logger::debug("SCRIPT") << "[810E] [=] void reg_anim_func(int mode, int arg)" << std::endl;
                auto arg = _script->dataStack()->pop(); // pointer or integer
                auto p1 = _script->dataStack()->popInteger();
                switch (p1)
                {
                    case 0x1: // ANIM_BEGIN
                    {
                        // @TODO: implement
                        // auto arg = popDataInteger();
                        // RB_UNRESERVED (1) - unreserved sequence, may not play, if there are no free slots left
                        // RB_RESERVED (2) - reserved sequence, should always play
                        break;
                    }
                    case 0x2: // ANIM_CLEAR
                    {
                        auto object = arg.objectValue();
                        if (auto critterObject = dynamic_cast<Game::CritterObject*>(object))
                        {
                            critterObject->stopMovement();
                        }
                        else
                        {
                            auto queue = dynamic_cast<UI::AnimationQueue*>(object->ui());
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
                        _error("reg_anim_func - unsupported mode");
                    }
                }
            }
        }
    }
}
