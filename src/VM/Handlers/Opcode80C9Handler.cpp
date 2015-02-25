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
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80C9Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/ArmorItemObject.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DrugItemObject.h"
#include "../../Game/WeaponItemObject.h"
#include "../../Game/AmmoItemObject.h"
#include "../../Game/MiscItemObject.h"
#include "../../Game/KeyItemObject.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode80C9Handler::Opcode80C9Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80C9Handler::_run()
{
    Logger::debug("SCRIPT") << "[80C9] [+] int obj_item_subtype(GameItemObject* object)" << std::endl;
<<<<<<< HEAD
    auto object = _vm->dataStack()->popObject();
    if      (dynamic_cast<Game::GameArmorItemObject*>(object))     _vm->dataStack()->push(0);
    else if (dynamic_cast<Game::GameContainerItemObject*>(object)) _vm->dataStack()->push(1);
    else if (dynamic_cast<Game::GameDrugItemObject*>(object))      _vm->dataStack()->push(2);
    else if (dynamic_cast<Game::GameWeaponItemObject*>(object))    _vm->dataStack()->push(3);
    else if (dynamic_cast<Game::GameAmmoItemObject*>(object))      _vm->dataStack()->push(4);
    else if (dynamic_cast<Game::GameMiscItemObject*>(object))      _vm->dataStack()->push(5);
    else if (dynamic_cast<Game::GameKeyItemObject*>(object))       _vm->dataStack()->push(6);
    else _vm->dataStack()->push(-1);
=======
    auto pointer = _vm->popDataObject();
    if      (static_cast<Game::GameArmorItemObject*>(pointer))     _vm->pushDataInteger(0);
    else if (static_cast<Game::GameContainerItemObject*>(pointer)) _vm->pushDataInteger(1);
    else if (static_cast<Game::GameDrugItemObject*>(pointer))      _vm->pushDataInteger(2);
    else if (static_cast<Game::GameWeaponItemObject*>(pointer))    _vm->pushDataInteger(3);
    else if (static_cast<Game::GameAmmoItemObject*>(pointer))      _vm->pushDataInteger(4);
    else if (static_cast<Game::GameMiscItemObject*>(pointer))      _vm->pushDataInteger(5);
    else if (static_cast<Game::GameKeyItemObject*>(pointer))       _vm->pushDataInteger(6);
    else _vm->pushDataInteger(-1);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
}

}


