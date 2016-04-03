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
#include "../../VM/Handler/Opcode8121Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/DudeObject.h"
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
            Opcode8121::Opcode8121(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8121::_run()
            {
                Logger::debug("SCRIPT") << "[8121] [+] void giQ_Option(int iq_test, int msg_list, int msg_num, procedure target, int reaction)" << std::endl;

                auto reaction = _script->dataStack()->popInteger();
                auto function = _script->dataStack()->popInteger();
                std::string text;
                if (_script->dataStack()->top().type() == StackValue::Type::STRING)
                {
                    text = _script->dataStack()->popString();
                    _script->dataStack()->popInteger(); // msg_list
                }
                else
                {
                    auto msg_num = _script->dataStack()->popInteger();
                    auto msg_file_num = _script->dataStack()->popInteger();
                    text = _script->msgMessage(msg_file_num, msg_num);
                }
                auto iq = _script->dataStack()->popInteger();
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
    }
}
