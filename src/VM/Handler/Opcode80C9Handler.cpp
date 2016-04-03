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
#include "../../VM/Handler/Opcode80C9Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../Game/AmmoItemObject.h"
#include "../../Game/ArmorItemObject.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DrugItemObject.h"
#include "../../Game/Game.h"
#include "../../Game/KeyItemObject.h"
#include "../../Game/MiscItemObject.h"
#include "../../Game/Object.h"
#include "../../Game/WeaponItemObject.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C9::Opcode80C9(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode80C9::_run()
            {
                Logger::debug("SCRIPT") << "[80C9] [+] int obj_item_subtype(GameItemObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if      (dynamic_cast<Game::ArmorItemObject*>(object))     _script->dataStack()->push(0);
                else if (dynamic_cast<Game::ContainerItemObject*>(object)) _script->dataStack()->push(1);
                else if (dynamic_cast<Game::DrugItemObject*>(object))      _script->dataStack()->push(2);
                else if (dynamic_cast<Game::WeaponItemObject*>(object))    _script->dataStack()->push(3);
                else if (dynamic_cast<Game::AmmoItemObject*>(object))      _script->dataStack()->push(4);
                else if (dynamic_cast<Game::MiscItemObject*>(object))      _script->dataStack()->push(5);
                else if (dynamic_cast<Game::KeyItemObject*>(object))       _script->dataStack()->push(6);
                else _script->dataStack()->push(-1);
            }
        }
    }
}


