/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../../VM/Handler/Opcode80DEHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DE::Opcode80DE(VM::Script* script) : OpcodeHandler(script)
            {
            }
            
            void Opcode80DE::_run()
            {
                Logger::debug("SCRIPT") << "[80DE] [*] void start_gdialog(int msgFileID, GameCritterObject* critter, int mood, int headID, int backgroundID)" << std::endl;
                int backgroundID = _script->dataStack()->popInteger();
                int headID = _script->dataStack()->popInteger();
                int mood = _script->dataStack()->popInteger();
            
                auto critter = dynamic_cast<Game::CritterObject*>(_script->dataStack()->popObject());
                if (!critter) _error("start_gdialog - wrong critter pointer");
            
                int msgFileID = _script->dataStack()->popInteger();
            
                auto interact = new State::CritterInteract();
                interact->setBackgroundID(backgroundID);
                interact->setHeadID(headID);
                interact->setMood(mood);
                interact->setCritter(critter);
                interact->setMsgFileID(msgFileID);
                interact->setScript(_script);
                Game::getInstance()->pushState(interact);
            }
        }
    }
}
