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
#include "../../VM/Handler/Opcode810CHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/CritterObject.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810C::Opcode810C(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode810C::_run()
            {
                int direction = _script->dataStack()->popInteger();
                int animation = _script->dataStack()->popInteger();
                auto object = static_cast<Game::Object*>(_script->dataStack()->popObject());

                Logger::debug("SCRIPT") << "[810C] [*] void anim(GameCritterObject* who, int animation, int direction)" << std::endl
                                        << "    direction = 0x" << std::hex << direction << std::endl
                                        << "    animation = 0x" << std::hex << animation << std::endl;
                switch (animation)
                {
                    case 1000: // ANIMATE_ROTATION. direction is orientation
                    {
                        object->setOrientation(direction);
                        //critter->setActionAnimation("aa");
                        break;
                    }
                    case 1010: // ANIMATE_SET_FRAME. direction is frame number
                    {
                        _warning("op_anim - unimplemented ANIMATE_SET_FRAME");
                        break;
                    }
                    default: //  set animation? direction is forward/backward
                    {
                        _warning("op_anim - unimplemented animation: " + std::to_string(animation));
                        break;
                    }
                }
            }
        }
    }
}
