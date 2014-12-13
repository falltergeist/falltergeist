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
#include "../../Game.h"
#include "../../States/LocationState.h"
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode8014Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackIntValue.h"
#include "../../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

Opcode8014Handler::Opcode8014Handler(Falltergeist::VM *vm) : OpcodeHandler(vm)
{
}

void Opcode8014Handler::_run()
{
    auto& debug = Logger::debug("SCRIPT");
    auto game = Game::getInstance();
    auto EVARS = game->locationState()->EVARS();
    std::string name;
    switch (_vm->dataStack()->top()->type())
    {
        case VMStackValue::TYPE_INTEGER:
            name = _vm->script()->identificators()->at(_vm->popDataInteger());
            break;
        case VMStackValue::TYPE_POINTER:
        {
            name = *static_cast<std::string*>(_vm->popDataPointer());
            break;
        }
        default:
            throw Exception("VM::opcode8014 error");
    }

    auto value = EVARS->at(name);
    _vm->dataStack()->push(value);

    debug << "[8014] [+] value = getExported(name)" << std::endl;
    debug << "    name = " << name << std::endl;
    debug << "    type = " << value->type() << std::endl;
    switch (value->type())
    {
        case VMStackValue::TYPE_INTEGER:
            debug << "    value = " << std::hex << ((VMStackIntValue*)value)->value() << std::endl;
            break;
    }
}
}
