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
#include "../../VM/Handlers/Opcode8116Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/CritterObject.h"
#include "../../Game/ContainerItemObject.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode8116Handler::Opcode8116Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8116Handler::_run()
{
    Logger::debug("SCRIPT") << "[8116] [+] void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)" << std::endl;
    auto amount = _vm->dataStack()->popInteger();
    auto item = dynamic_cast<Game::ItemObject*>(_vm->dataStack()->popObject());
    if (!item) _error("add_mult_objs_to_inven - item not instanceof GameItemObject");
    item->setAmount(amount);
    // who can be critter or container
    auto object = _vm->dataStack()->popObject();
    if (auto critter = dynamic_cast<Game::CritterObject*>(object))
    {
        critter->inventory()->push_back(item);
    }
    else if (auto container = dynamic_cast<Game::ContainerItemObject*>(object))
    {
        container->inventory()->push_back(item);
    }
    else
    {
        _error("add_mult_objs_to_inven - wrong WHO parameter");
    }
}

}


