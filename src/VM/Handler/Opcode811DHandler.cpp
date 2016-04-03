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
#include "../../VM/Handler/Opcode811DHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/CritterDialog.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode811D::Opcode811D(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode811D::_run()
            {
                Logger::debug("SCRIPT") << "[811D] [?] gsay_end" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog*>(Game::getInstance()->topState());
                if (dialog->hasAnswers())
                {
                    _script->dataStack()->push(0); // function return value
                    throw HaltException();
                }
                Game::getInstance()->popState(); // dialog state
            }
        }
    }
}


