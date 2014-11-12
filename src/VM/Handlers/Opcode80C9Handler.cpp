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
#include "../../Engine/Logger.h"
#include "../../VM/Handlers/Opcode80C9Handler.h"
#include "../../Engine/Exception.h"
#include "../../Engine/Game.h"
#include "../../Game/GameObject.h"
#include "../../Game/GameArmorItemObject.h"
#include "../../Game/GameContainerItemObject.h"
#include "../../Game/GameDrugItemObject.h"
#include "../../Game/GameWeaponItemObject.h"
#include "../../Game/GameAmmoItemObject.h"
#include "../../Game/GameMiscItemObject.h"
#include "../../Game/GameKeyItemObject.h"
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
    auto pointer = _vm->popDataPointer();
    if      (static_cast<GameArmorItemObject*>(pointer))     _vm->pushDataInteger(0);
    else if (static_cast<GameContainerItemObject*>(pointer)) _vm->pushDataInteger(1);
    else if (static_cast<GameDrugItemObject*>(pointer))      _vm->pushDataInteger(2);
    else if (static_cast<GameWeaponItemObject*>(pointer))    _vm->pushDataInteger(3);
    else if (static_cast<GameAmmoItemObject*>(pointer))      _vm->pushDataInteger(4);
    else if (static_cast<GameMiscItemObject*>(pointer))      _vm->pushDataInteger(5);
    else if (static_cast<GameKeyItemObject*>(pointer))       _vm->pushDataInteger(6);
    else _vm->pushDataInteger(-1);
}

}


