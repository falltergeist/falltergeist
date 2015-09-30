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
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/CritterDialog.h"
#include "../../VM/Handlers/Opcode811DHandler.h"
#include "../../VM/VMHaltException.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode811DHandler::Opcode811DHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode811DHandler::_run()
{
    Logger::debug("SCRIPT") << "[811D] [?] gsay_end" << std::endl;
    auto dialog = dynamic_cast<State::CritterDialog*>(Game::getInstance()->topState());
    if (dialog->hasAnswers())
    {
        _vm->dataStack()->push(0); // function return value
        throw VMHaltException();
    }
    Game::getInstance()->popState(); // dialog state
}

}


