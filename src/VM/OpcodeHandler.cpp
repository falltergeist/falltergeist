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
#include "../VM/OpcodeHandler.h"

// C++ standard includes

// Falltergeist includes
#include "../Format/Int/File.h"
#include "../Logger.h"
#include "../VM/ErrorException.h"
#include "../VM/Script.h"

// Third party icnludes

namespace Falltergeist
{
    namespace VM
    {
        OpcodeHandler::OpcodeHandler(VM::Script* script) : _script(script)
        {
            _offset = script->programCounter();
        }

        OpcodeHandler::~OpcodeHandler()
        {
        }

        void OpcodeHandler::run()
        {
            _script->setProgramCounter(_script->programCounter() + 2);
            _run();
        }

        void OpcodeHandler::_run()
        {
        }

        void OpcodeHandler::_warning(const std::string& message)
        {
            Logger::warning("SCRIPT") << message << " at " << _script->script()->filename() << ":0x" << std::hex << _offset << std::endl;
        }

        void OpcodeHandler::_error(const std::string& message)
        {
            throw ErrorException(message);
        }
    }
}
