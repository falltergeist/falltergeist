/*
 * Copyright 2012-2018 Falltergeist Developers.
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

// C++ standard includes
#include "FalloutValue.h"

// Falltergeist includes

// Third party includes

namespace Falltergeist {
    namespace VM {
        FalloutValue::FalloutValue(int value) {
            _type = Type::INTEGER;
            _integerValue = value;
        }

        FalloutValue::FalloutValue(const std::string &value) {
            _type = Type::STRING;
            _stringValue = value;
        }

        FalloutValue::Type FalloutValue::type() const {
            return _type;
        }

        int FalloutValue::asInteger() const {

            if (!aValue.isNumber() || !bValue.isNumber()) {
                _error(std::string("op_bwand: invalid argument types: ") + aValue.typeName() + " bwand " +
                       bValue.typeName());
            }

            return _integerValue;
        }

        std::string FalloutValue::asString() const {
            return _stringValue;
        }

        std::shared_ptr<IFalloutValue> FalloutValue::add(std::shared_ptr<IFalloutValue> value) const
        {
            switch (bValue.type()) {
                case StackValue::Type::INTEGER: // INTEGER
                {
                    int arg2 = bValue.integerValue();
                    switch (aValue.type()) {
                        case StackValue::Type::INTEGER: // INTEGER + INTEGER
                        {
                            _script->dataStack()->push(aValue.integerValue() + arg2);
                            break;
                        }
                        case StackValue::Type::FLOAT: // FLOAT + INTEGER
                        {
                            _script->dataStack()->push(aValue.floatValue() + (float) arg2);
                            break;
                        }
                        case StackValue::Type::STRING: // STRING + INTEGER
                        {
                            std::string arg1 = aValue.stringValue();
                            _script->dataStack()->push(arg1 + bValue.toString());
                            break;
                        }
                        default: {
                            _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                        }
                    }
                    break;
                }
                case StackValue::Type::STRING: {
                    auto arg2 = bValue.stringValue();
                    switch (aValue.type()) {
                        case StackValue::Type::STRING: // STRING + STRING
                        {
                            _script->dataStack()->push(aValue.stringValue() + arg2);
                            break;
                        }
                        case StackValue::Type::FLOAT: // FLOAT + STRING
                        {
                            _error("op_add - FLOAT+STRING not allowed");
                            break;
                        }
                        case StackValue::Type::INTEGER: // INTEGER + STRING
                        {
                            _error("op_add - INTEGER+STRING not allowed");
                            break;
                        }
                        default: {
                            _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                        }
                    }
                    break;
                }
                case StackValue::Type::FLOAT: // FLOAT
                {
                    auto arg2 = bValue.floatValue();
                    switch (aValue.type()) {
                        case StackValue::Type::INTEGER: // INTEGER + FLOAT
                        {
                            _script->dataStack()->push((float) aValue.integerValue() + arg2);
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
                        default: {
                            _error(std::string("op_add - invalid left argument type: ") + aValue.typeName());
                        }
                    }
                    break;
                }
                default: {
                    _error(std::string("op_add - invalid right argument type: ") + bValue.typeName());
                }
            }
        }
    }
}

