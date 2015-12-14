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

#ifndef FALLTERGEIST_OPCODEHANDLER_H
#define FALLTERGEIST_OPCODEHANDLER_H

// C++ standard includes
#include <memory>
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class VM;

class OpcodeHandler
{
protected:
    VM* _vm;
    unsigned int _offset;

    virtual void _run();
    // print warning message to log
    void _warning(const std::string& message);
    // prints error message to logs and throws VMErrorException
    void _error(const std::string& message);
public:
    OpcodeHandler(VM* vm);
    virtual ~OpcodeHandler();
    void run();
};

}
#endif // FALLTERGEIST_OPCODEHANDLER_H
