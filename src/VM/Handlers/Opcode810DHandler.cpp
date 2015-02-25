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
#include <algorithm>

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode810DHandler.h"
#include "../../VM/VM.h"
#include "../../Game/CritterObject.h"

// Third party includes

namespace Falltergeist
{

Opcode810DHandler::Opcode810DHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode810DHandler::_run()
{
    Logger::debug("SCRIPT") << "[810D] [=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
    const int pid = _vm->dataStack()->popInteger();
    auto who = _vm->dataStack()->popObject();
    if (auto critter = dynamic_cast<Game::GameCritterObject*>((Game::GameObject*)who))
    {
        auto iterator = std::find_if(critter->inventory()->begin(), critter->inventory()->end(),
                                    [&] (Game::GameItemObject * &item) { return item->PID() == pid; });
        const bool found = iterator != critter->inventory()->end();
        _vm->pushDataObject(found ? *iterator : nullptr);
    }
    else
    {
        Logger::warning("SCRIPT") << "[810D] - 'who' is not valid GameCritterObject. It is " << std::string(typeid(who).name());
        _vm->pushDataObject(nullptr);
    }
}

}
