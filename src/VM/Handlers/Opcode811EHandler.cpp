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
#include "../../VM/Handlers/Opcode811EHandler.h"
#include "../../VM/VMStackValue.h"
#include "../../VM/VM.h"

// Third party includes

namespace Falltergeist
{

Opcode811EHandler::Opcode811EHandler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode811EHandler::_run()
{
    Logger::debug("SCRIPT") << "[811E] [=] void gSay_Reply(int msg_file_num, int msg_num)" << std::endl;
    auto dialog = dynamic_cast<State::CritterDialog*>(Game::getInstance()->states()->back());
    dialog->deleteAnswers();
    if (_vm->dataStack()->top().type() == VMStackValue::TYPE_STRING)
    {
        auto question = _vm->dataStack()->popString();
        dialog->setQuestion(question);
    }
    else
    {
        auto msg_num = _vm->dataStack()->popInteger();
        auto msg_file_num = _vm->dataStack()->popInteger();
        dialog->setQuestion(_vm->msgMessage(msg_file_num, msg_num));
    }
}

}


