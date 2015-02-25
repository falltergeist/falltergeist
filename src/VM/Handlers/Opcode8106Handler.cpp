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
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode8106Handler.h"
#include "../../Exception.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/CritterObject.h"
#include "../../Game/ObjectFactory.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode8106Handler::Opcode8106Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8106Handler::_run()
{
    Logger::debug("SCRIPT") << "[8106] [=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)" << std::endl;
    auto where = _vm->popDataInteger();
    auto critter = static_cast<Game::GameCritterObject*>(_vm->popDataObject());
    switch (where)
    {
    case 0: // ARMOR SLOT
        _vm->pushDataObject(critter->armorSlot());
        break;
    case 1: // RIGHT HAND SLOT
        _vm->pushDataObject(critter->rightHandSlot());
        break;
    case 2: // LEFT HAND SLOT
        _vm->pushDataObject(critter->leftHandSlot());
        break;
    case -2: // INVENTORY COUNT
        _vm->pushDataInteger(critter->inventory()->size());
        break;
    default:
        throw Exception("VM::opcode8106 error");
    }
}

}


