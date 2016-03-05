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

// C++ standard includes

// Falltergeist includes
#include <Game/Game.h>
#include <State/Location.h>
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80E9Handler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80E9Handler::Opcode80E9Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80E9Handler::_run()
{
    Logger::debug("SCRIPT") << "[80E9] [*] void set_light_level(int level)" << std::endl;
    auto level = _vm->dataStack()->popInteger();
    if (level<0) level=0;
    if (level>100) level=100;

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
