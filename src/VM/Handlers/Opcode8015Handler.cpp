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
#include "../../Engine/Game.h"
#include "../../States/LocationState.h"
#include "../../Engine/Logger.h"
#include "../../VM/Handlers/Opcode8015Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode8015Handler::Opcode8015Handler(Falltergeist::VM *vm) : OpcodeHandler(vm)
{
}

void Opcode8015Handler::_run()
{
    Logger::debug("SCRIPT") << "[8015] [*] export(value, name)" << std::endl;
    auto name = static_cast<std::string*>(_vm->popDataPointer());
    auto value = _vm->dataStack()->pop();
    auto game = Game::getInstance();
    auto EVARS = game->locationState()->EVARS();
    EVARS->at(*name) = value;
}

}
