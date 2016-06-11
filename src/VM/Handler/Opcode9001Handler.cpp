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
#include "../../VM/Handler/Opcode9001Handler.h"

// C++ standard includes

// Falltergeist includes
#include "../../Format/Int/File.h"
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode9001::Opcode9001(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode9001::_run()
            {
                unsigned int data;
                unsigned short nextOpcode;
                *(_script->script()) >> data >> nextOpcode;

                // Skip 4 readed bytes
                _script->setProgramCounter(_script->programCounter() + 4);

                switch(nextOpcode)
                {
                    case 0x8014: // get exported var value
                    case 0x8015: // set exported var value
                    case 0x8016: // export var
                    {
                        _script->dataStack()->push(_script->script()->identifiers()->at(data));
                        break;
                    }
                    default:
                    {
                        _script->dataStack()->push(_script->script()->strings()->at(data));
                        break;
                    }
                }

                auto value = _script->dataStack()->top();
                auto& debug = Logger::debug("SCRIPT");
                debug   << "[9001] [*] push_d string" << std::endl
                        << "     type: " << value.typeName() << std::endl
                        << "    value: " << value.toString() << std::endl;
            }
        }
    }
}
