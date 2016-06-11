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
#include "../../VM/Handler/Opcode8039Handler.h"

// C++ standard includes

// Falltergeist includes
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
            Opcode8039::Opcode8039(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode8039::_run()
            {
                auto& debug = Logger::debug("SCRIPT");
                debug << "[8039] [*] op_add(aValue, bValue)" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                debug << "    types: " << aValue.typeName() << " + " << bValue.typeName() << std::endl;
                switch (bValue.type())
                {
                    case StackValue::Type::INTEGER: // INTEGER
                    {
                        int arg2 = bValue.integerValue();
                        switch (aValue.type())
                        {
                            case StackValue::Type::INTEGER: // INTEGER + INTEGER
                            {
                                _script->dataStack()->push(aValue.integerValue() + arg2);
                                break;
                            }
                            case StackValue::Type::FLOAT: // FLOAT + INTEGER
                            {
                                _script->dataStack()->push(aValue.floatValue() + (float)arg2);
                                break;
                            }
                            case StackValue::Type::STRING: // STRING + INTEGER
                            {
                                std::string arg1 = aValue.stringValue();
                                _script->dataStack()->push(arg1 + bValue.toString());
                                break;
                            }
                            default:
                            {
                                _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                            }
                        }
                        break;
                    }
                    case StackValue::Type::STRING:
                    {
                        auto arg2 = bValue.stringValue();
                        switch (aValue.type())
                        {
                            case StackValue::Type::STRING: // STRING + STRING
                            {
                                _script->dataStack()->push(aValue.stringValue() + arg2);
                                break;
                            }
                            case StackValue::Type::FLOAT: // FLOAT + STRING
                            {
                                _error("op_add - FLOAT+STRING not allowed");
                            }
                            case StackValue::Type::INTEGER: // INTEGER + STRING
                            {
                                _error("op_add - INTEGER+STRING not allowed");
                            }
                            default:
                            {
                                _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                            }
                        }
                        break;
                    }
                    case StackValue::Type::FLOAT: // FLOAT
                    {
                        auto arg2 = bValue.floatValue();
                        switch (aValue.type())
                        {
                            case StackValue::Type::INTEGER: // INTEGER + FLOAT
                            {
                                _script->dataStack()->push((float)aValue.integerValue() + arg2);
                                break;
                            }
                            case StackValue::Type::FLOAT: // FLOAT + FLOAT
                            {
                                _script->dataStack()->push(aValue.floatValue() + arg2);
                                break;
                            }
                            case StackValue::Type::STRING: // STRING + FLOAT
                            {
                                auto arg1 = aValue.stringValue();
                                _script->dataStack()->push(arg1 + bValue.toString());
                                break;
                            }
                            default:
                            {
                                _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                            }
                        }
                        break;
                    }
                    default:
                    {
                        _error(std::string("op_add - invalid right argument type: ") + bValue.typeName());
                    }
                }
            }
        }
    }
}
