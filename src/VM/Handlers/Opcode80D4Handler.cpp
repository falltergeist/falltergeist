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
#include "../../VM/Handlers/Opcode80D4Handler.h"
#include "../../Exception.h"
#include "../../Game.h"
#include "../../ResourceManager.h"
#include "../../Game/GameObject.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode80D4Handler::Opcode80D4Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80D4Handler::_run()
{
    Logger::debug("SCRIPT") << "[80D4] [+] int objectPosition(GameObject* object)" << std::endl;
    auto object = static_cast<GameObject*>(_vm->popDataPointer());
    if (!object) throw new Exception("Opcode 80d4 error");
    _vm->pushDataInteger(object->hexagon()->number());
}

}


