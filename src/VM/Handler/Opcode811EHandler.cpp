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

// Related headers
#include "../../VM/Handler/Opcode811EHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/CritterDialog.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode811E::Opcode811E(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode811E::_run()
            {
                Logger::debug("SCRIPT") << "[811E] [=] void gSay_Reply(int msg_file_num, int msg_num)" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog*>(Game::getInstance()->topState());
                dialog->deleteAnswers();
                if (_script->dataStack()->top().type() == StackValue::Type::STRING)
                {
                    auto question = _script->dataStack()->popString();
                    dialog->setQuestion(question);
                }
                else
                {
                    auto msg_num = _script->dataStack()->popInteger();
                    auto msg_file_num = _script->dataStack()->popInteger();
                    dialog->setQuestion(_script->msgMessage(msg_file_num, msg_num));
                }
            }
        }
    }
}
