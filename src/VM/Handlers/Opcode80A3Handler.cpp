/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include "../../VM/Handlers/Opcode80A3Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Audio/Mixer.h"
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80A3Handler::Opcode80A3Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80A3Handler::_run()
{
    Logger::debug("SCRIPT") << "[80A3] [=] void play_sfx(string* p1)" << std::endl;
    auto name = _vm->dataStack()->popString();
    Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/" + name + ".acm");
}

}


