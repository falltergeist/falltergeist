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

#ifndef FALLTERGEIST_VM_OPCODEHANDLER_H
#define FALLTERGEIST_VM_OPCODEHANDLER_H

// C++ standard includes
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        class Script;

        class OpcodeHandler
        {
            public:
                OpcodeHandler(VM::Script* script);
                virtual ~OpcodeHandler();
                void run();
            protected:
                VM::Script* _script;
                unsigned int _offset;

                virtual void _run();
                // print warning message to log
                void _warning(const std::string& message);
                // prints error message to logs and throws VM::ErrorException
                void _error(const std::string& message);
        };
    }
}
#endif // FALLTERGEIST_VM_OPCODEHANDLER_H
