/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_OPCODE8033HANDLER_H
#define FALLTERGEIST_OPCODE8033HANDLER_H

// C++ standard includes

// Falltergeist includes
#include "../../VM/OpcodeHandler.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{

class OpcodeComparisonHandler : public OpcodeHandler
{
public:
    enum class Cmp { EQUAL = 1, NOT_EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL };
    
    OpcodeComparisonHandler(VM* vm, Cmp cmpType);

private:
    Cmp _cmpType;
    void _run();
    const char* _cmpOpcodeName();
    
    template <class T1, class T2> 
    int _compare(T1 arg1, T2 arg2)
    {
        switch (_cmpType)
        {
            case Cmp::EQUAL:
            {
                return arg1 == arg2;
            }
            case Cmp::NOT_EQUAL:
            {
                return arg1 != arg2;
            }
            case Cmp::LESS:
            {
                return arg1 < arg2;
            }
            case Cmp::LESS_EQUAL:
            {
                return arg1 <= arg2;
            }
            case Cmp::GREATER:
            {
                return arg1 > arg2;
            }
            case Cmp::GREATER_EQUAL:
            {
                return arg1 >= arg2;
            }
        }
    }
};

}
#endif // FALLTERGEIST_OPCODE8033HANDLER_H
