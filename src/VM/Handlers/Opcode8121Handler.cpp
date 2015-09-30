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
#include "../../VM/Handlers/Opcode8121Handler.h"
#include "../../VM/VM.h"
#include "../../VM/VMStackValue.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../Game/DudeObject.h"

// Third party includes

namespace Falltergeist
{

Opcode8121Handler::Opcode8121Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode8121Handler::_run()
{
    Logger::debug("SCRIPT") << "[8121] [+] void giQ_Option(int iq_test, int msg_list, int msg_num, procedure target, int reaction)" << std::endl;

    auto reaction = _vm->dataStack()->popInteger();
    auto function = _vm->dataStack()->popInteger();
    std::string text;
    if (_vm->dataStack()->top().type() == VMStackValue::Type::STRING)
    {
        text = _vm->dataStack()->popString();
        _vm->dataStack()->popInteger(); // msg_list
    }
    else
    {
        auto msg_num = _vm->dataStack()->popInteger();
        auto msg_file_num = _vm->dataStack()->popInteger();
        text = _vm->msgMessage(msg_file_num, msg_num);
    }
    auto iq = _vm->dataStack()->popInteger();
    auto game = Game::getInstance();
    auto dialog = dynamic_cast<State::CritterDialog*>(game->topState());
    if (iq >= 0)
    {
        if (game->player()->stat(STAT::INTELLIGENCE) >= iq)
        {
            dialog->reactions()->push_back(reaction);
            dialog->functions()->push_back(function);
            dialog->addAnswer(text);
        }
    }
    if (iq < 0)
    {
        if (game->player()->stat(STAT::INTELLIGENCE) <= abs(iq))
        {
            dialog->reactions()->push_back(reaction);
            dialog->functions()->push_back(function);
            dialog->addAnswer(text);
        }
    }
}

}


