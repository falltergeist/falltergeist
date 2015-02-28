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
    enum {CMP_EQUAL = 1, CMP_NOT_EQUAL, CMP_LESS, CMP_LESS_EQUAL, CMP_GREATER, CMP_GREATER_EQUAL};
    
    OpcodeComparisonHandler(VM* vm, int cmpType);
private:
    int _cmpType;
    void _run();
    const char* _cmpOpcodeName();
    
    template <class T1, class T2> 
    int _compare(T1 arg1, T2 arg2)
    {
        switch (_cmpType)
        {
            case CMP_EQUAL: 
            {
                return arg1 == arg2;
            }
            case CMP_NOT_EQUAL: 
            {
                return arg1 != arg2;
            }
            case CMP_LESS: 
            {
                return arg1 < arg2;
            }
            case CMP_LESS_EQUAL: 
            {
                return arg1 <= arg2;
            }
            case CMP_GREATER: 
            {
                return arg1 > arg2;
            }
            case CMP_GREATER_EQUAL: 
            {
                return arg1 >= arg2;
            }
            default:
            {
                throw Exception("Invalid compare type!");
            }
        }
    }
};

}
#endif // FALLTERGEIST_OPCODE8033HANDLER_H
