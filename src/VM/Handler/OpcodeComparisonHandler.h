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

#ifndef FALLTERGEIST_VM_HANDLER_OPCODE8033_H
#define FALLTERGEIST_VM_HANDLER_OPCODE8033_H

// C++ standard includes

// Falltergeist includes
#include "../../VM/OpcodeHandler.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class OpcodeComparison : public OpcodeHandler
            {
                public:
                    enum class Type
                    {
                        EQUAL = 1,
                        NOT_EQUAL,
                        LESS,
                        LESS_EQUAL,
                        GREATER,
                        GREATER_EQUAL
                    };

                    OpcodeComparison(VM::Script* script, Type cmpType);

                private:
                    Type _cmpType;
                    void _run();
                    const char* _cmpOpcodeName();

                    template <class T1, class T2>
                    int _compare(T1 arg1, T2 arg2)
                    {
                        switch (_cmpType)
                        {
                            case Type::EQUAL:
                            {
                                return arg1 == arg2;
                            }
                            case Type::NOT_EQUAL:
                            {
                                return arg1 != arg2;
                            }
                            case Type::LESS:
                            {
                                return arg1 < arg2;
                            }
                            case Type::LESS_EQUAL:
                            {
                                return arg1 <= arg2;
                            }
                            case Type::GREATER:
                            {
                                return arg1 > arg2;
                            }
                            case Type::GREATER_EQUAL:
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
    }
}
#endif // FALLTERGEIST_VM_HANDLER_OPCODE8033_H
