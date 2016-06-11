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

// Related headers
#include "../../VM/Handler/Opcode80E9Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E9::Opcode80E9(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80E9::_run()
            {
                Logger::debug("SCRIPT") << "[80E9] [*] void set_light_level(int level)" << std::endl;
                auto level = _script->dataStack()->popInteger();

                if (level > 100 || level < 0)
                {
                    _warning("set_light_level: level should be 0-100");
                    return;
                }

                unsigned int light;
                if ( level < 50 )
                {
                    light = 0x4000 + level * 0x6000 / 100;
                }
                else if ( level == 50 )
                {
                    light = 0xA000;
                }
                else
                {
                    light = 0xA000 + level * 0x6000 / 100;
                }

                Game::getInstance()->locationState()->setLightLevel(light);
            }
        }
    }
}
