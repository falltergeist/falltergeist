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
#include "../../VM/Handler/OpcodeC001Handler.h"

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
            OpcodeC001::OpcodeC001(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void OpcodeC001::_run()
            {
                int value;
                *(_script->script()) >> value;

                // Skip 4 bytes for readed integer value
                _script->setProgramCounter(_script->programCounter() + 4);
                _script->dataStack()->push(StackValue(value));

                auto& debug = Logger::debug("SCRIPT");
                debug << "[C001] [*] push_d integer" << std::endl;
                debug << "    value: " << std::to_string(value) << std::endl;
            }
        }
    }
}
