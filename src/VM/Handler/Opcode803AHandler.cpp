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
#include "../../VM/Handler/Opcode803AHandler.h"

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
            Opcode803A::Opcode803A(VM::Script* script) : OpcodeHandler(script)
            {
            }

            void Opcode803A::_run()
            {
                Logger::debug("SCRIPT") << "[803A] [*] op_sub(a, b) -" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                if (!bValue.isNumber() || !aValue.isNumber())
                {
                    _error(std::string("op_sub(a, b): Incompatible types: ") + aValue.typeName() + " - " + bValue.typeName());
                }
                if (aValue.type() == StackValue::Type::INTEGER)
                {
                    if (bValue.type() == StackValue::Type::INTEGER)
                    {
                        _script->dataStack()->push(aValue.integerValue() - bValue.integerValue());
                    }
                    else
                    {
                        _script->dataStack()->push((float)aValue.integerValue() - bValue.floatValue());
                    }
                }
                else
                {
                    if (bValue.type() == StackValue::Type::INTEGER)
                    {
                        _script->dataStack()->push(aValue.floatValue() - (float)bValue.integerValue());
                    }
                    else
                    {
                        _script->dataStack()->push(aValue.floatValue() - bValue.floatValue());
                    }
                }
            }
        }
    }
}
