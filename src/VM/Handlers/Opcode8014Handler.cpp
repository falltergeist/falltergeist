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
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Exception.h"
#include "../../Engine/Game.h"
#include "../../Engine/Location.h"
#include "../../VM/Handlers/Opcode8014Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode8014Handler::Opcode8014Handler(Falltergeist::VM *vm) : OpcodeHandler(vm)
{
}

void Opcode8014Handler::_run()
{
    CrossPlatform::debug("[*] getExported(name)", DEBUG_SCRIPT);
    auto game = Game::getInstance();
    auto EVARS = game->location()->EVARS();
    switch (_vm->dataStack()->top()->type())
    {
        case VMStackValue::TYPE_INTEGER:
            _vm->dataStack()->push(EVARS->at(_vm->script()->identificators()->at(_vm->popDataInteger())));
            break;
        case VMStackValue::TYPE_POINTER:
        {
            auto string = std::static_pointer_cast<std::string>(_vm->popDataPointer());
            _vm->dataStack()->push(EVARS->at(*string.get()));
            break;
        }
        default:
            throw Exception("VM::opcode8014 error");
    }
}
}
