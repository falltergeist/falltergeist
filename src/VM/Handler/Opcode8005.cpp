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
#include "../../VM/Handler/Opcode8005.h"

// C++ standard includes

// Falltergeist includes
#include "../../Format/Int/File.h"
#include "../../Format/Int/Procedure.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8005::Opcode8005(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8005::_run()
            {
                auto functionIndex = _script->dataStack()->popInteger();
                // @TODO: pass arguments and call external procedures
                /*auto argumentCount = _script->dataStack()->popInteger();
                std::vector<int> args;
                for (int i = 0; i < argumentCount; i++)
                {
                    args.push_back(_script->dataStack()->popInteger());
                }*/
                _script->setProgramCounter(_script->script()->procedures()->at(functionIndex)->bodyOffset());
                Logger::debug("SCRIPT") << "[8005] [*] op_call(0x" << std::hex << functionIndex << ") = 0x" << _script->programCounter() << std::endl;
            }
        }
    }
}
