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

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../Logger.h"
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
    auto& debug = Logger::debug("SCRIPT");
    debug << "[8014] [+] value = op_fetch_external(name)" << std::endl;
    auto game = Game::getInstance();
    auto EVARS = game->locationState()->EVARS();
    std::string name;
    auto nameValue = _vm->dataStack()->pop();
    switch (nameValue.type())
    {
        case VMStackValue::TYPE_INTEGER:
            name = _vm->script()->identifiers()->at(nameValue.integerValue());
            break;
        case VMStackValue::TYPE_STRING:
        {
            name = nameValue.stringValue();
            break;
        }
        default:
            _error(std::string("op_fetch_external - invalid argument type: ") + nameValue.typeName());
    }
    debug << " name = " << name;
    if (EVARS->find(name) == EVARS->end())
    {
        _error(std::string() + "op_fetch_external: exported variable \"" + name + "\" not found.");
    }
    auto value = EVARS->at(name);
    debug << ", type = " << value.type() << ", value = " << value.toString() << std::endl;
    _vm->dataStack()->push(value);
}

}
