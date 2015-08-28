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
#include "../../Logger.h"
#include "../../Game/CritterObject.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
#include "../../VM/Handlers/Opcode80DEHandler.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode80DEHandler::Opcode80DEHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80DEHandler::_run()
{
    Logger::debug("SCRIPT") << "[80DE] [*] void start_gdialog(int msgFileID, GameCritterObject* critter, int mood, int headID, int backgroundID)" << std::endl;
    int backgroundID = _vm->dataStack()->popInteger();
    int headID = _vm->dataStack()->popInteger();
    int mood = _vm->dataStack()->popInteger();

    auto critter = dynamic_cast<Game::CritterObject*>(_vm->dataStack()->popObject());
    if (!critter) _error("start_gdialog - wrong critter pointer");

    int msgFileID = _vm->dataStack()->popInteger();

    auto interact = std::make_shared<State::CritterInteract>();
    interact->setBackgroundID(backgroundID);
    interact->setHeadID(headID);
    interact->setMood(mood);
    interact->setCritter(critter);
    interact->setMsgFileID(msgFileID);
    interact->setScript(_vm);
    Game::getInstance()->pushState(interact);
}

}
