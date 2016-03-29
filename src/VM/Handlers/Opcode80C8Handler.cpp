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
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80C8Handler.h"
#include "../../VM/VM.h"
#include "../../Game/Object.h"



// Third party includes

namespace Falltergeist
{

Opcode80C8Handler::Opcode80C8Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80C8Handler::_run()
{
    // @TODO: implement
    Logger::debug("SCRIPT") << "[80C8] [=] int obj_type(void* obj)" << std::endl;
    auto object = _vm->dataStack()->popObject();
    Game::Object::Type type = object->type();
    switch (type)
    {
        case Game::Object::Type::CRITTER:
        case Game::Object::Type::DUDE:
            _vm->dataStack()->push(1);
            break;
        default:
            _vm->dataStack()->push((int)type);
            break;

    }
    //_vm->dataStack()->push(object);
}

}


