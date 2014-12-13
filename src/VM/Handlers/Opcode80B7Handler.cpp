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
#include "../../VM/Handlers/Opcode80B7Handler.h"
#include "../../Exception.h"
#include "../../Game.h"
#include "../../ResourceManager.h"
#include "../../Game/GameObject.h"
#include "../../Game/GameObjectFactory.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/VM.h"



// Third party includes

namespace Falltergeist
{

Opcode80B7Handler::Opcode80B7Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80B7Handler::_run()
{
    Logger::debug("SCRIPT") << "[80B7] [+] GameObject* create_object_sid(int PID, int position, int elevation, int SID)" << std::endl;
    auto SID = _vm->popDataInteger();
    auto elevation = _vm->popDataInteger();
    auto position = _vm->popDataInteger();
    auto PID = _vm->popDataInteger();
    auto object = GameObjectFactory::createObject(PID);
    auto hexagon = Game::getInstance()->Location()->hexagonGrid()->at(position);
    State::Location::moveObjectToHexagon(object, hexagon);
    object->setElevation(elevation);
    if (SID > 0)
    {
        auto intFile = ResourceManager::intFileType(SID);
        if (intFile)
        {
            object->setScript(new VM(intFile, object));
        }
    }
    _vm->pushDataPointer(object);
}

}


