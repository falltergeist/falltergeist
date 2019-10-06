#include "VM/Fallout/Exception.h"
#include "VM/Fallout/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            StackValue::StackValue(int value)
            {
                _type = Type::INTEGER;
                _integerValue = value;
                _floatValue = (float) value;
                _stringValue = std::to_string(value);
                _objectValue = nullptr;
            }

            StackValue::StackValue(float value)
            {
                _type = Type::FLOAT;
                _integerValue = (int) value;
                _floatValue = value;
                _stringValue = std::to_string(value);
                _objectValue = nullptr;
            }

            StackValue::StackValue(const std::string &value)
            {
                _type = Type::STRING;
                _integerValue = std::stoi(value);
                _floatValue = std::stof(value);
                _stringValue = value;
                _objectValue = nullptr;
            }

            StackValue::StackValue(std::shared_ptr<Game::Object> value)
            {
                _type = Type::OBJECT;
                _integerValue = 0;
                _floatValue = 0;
                _objectValue = std::move(value);
            }

            StackValue::Type StackValue::type() const
            {
                return _type;
            }

            int StackValue::asInteger() const
            {
                return _integerValue;
            }

            float StackValue::asFloat() const
            {
                return _floatValue;
            }

            std::string StackValue::asString() const
            {
                return _stringValue;
            }

            std::shared_ptr<Game::Object> StackValue::asObject() const
            {
                return _objectValue;
            }

            std::shared_ptr<IStackValue> StackValue::add(std::shared_ptr<IStackValue> value) const
            {
                if (type() == Type::INTEGER  && value->type() == Type::INTEGER) {
                    int sum = asInteger() + value->asInteger();
                    return std::make_shared<StackValue>(sum);
                }

                if (type() == Type::INTEGER && value->type() == Type::FLOAT) {
                    float sum = asFloat() + value->asFloat();
                    return std::make_shared<StackValue>(sum);
                }

                if (type() == Type::INTEGER && value->type() == Type::STRING) {
                    int sum = asInteger() + value->asInteger();
                    return std::make_shared<StackValue>(sum);
                }

                if (type() == Type::FLOAT) {
                    float sum = asFloat() + value->asFloat();
                    return std::make_shared<StackValue>(sum);
                }

                if (type() == Type::STRING) {
                    std::string sum = asString() + value->asString();
                    return std::make_shared<StackValue>(sum);
                }

                throw Exception("Invalid operand types");
            }

            std::shared_ptr<IStackValue> StackValue::sub(std::shared_ptr<IStackValue> value) const
            {
                // TODO
                return nullptr;
    //            auto bValue = _script->dataStack()->pop();
    //            auto aValue = _script->dataStack()->pop();
    //            if (!bValue.isNumber() || !aValue.isNumber()) {
    //                _error(std::string("op_sub(a, b): Incompatible types: ") + aValue.typeName() + " - " +
    //                       bValue.typeName());
    //            }
    //            if (aValue.type() == StackValue::Type::INTEGER) {
    //                if (bValue.type() == StackValue::Type::INTEGER) {
    //                    _script->dataStack()->push(aValue.integerValue() - bValue.integerValue());
    //                } else {
    //                    _script->dataStack()->push((float) aValue.integerValue() - bValue.floatValue());
    //                }
    //            } else {
    //                if (bValue.type() == StackValue::Type::INTEGER) {
    //                    _script->dataStack()->push(aValue.floatValue() - (float) bValue.integerValue());
    //                } else {
    //                    _script->dataStack()->push(aValue.floatValue() - bValue.floatValue());
    //                }
    //            }
            }

            std::shared_ptr<IStackValue> StackValue::mul(std::shared_ptr<IStackValue> value) const
            {
                // TODO
                return nullptr;
    //            Logger::debug("SCRIPT") << "[803B] [*] op_mul(a, b) *" << std::endl;
    //            auto bValue = _script->dataStack()->pop();
    //            auto aValue = _script->dataStack()->pop();
    //            if (!bValue.isNumber() || !aValue.isNumber()) {
    //                _error(std::string("op_mul(a, b): Incompatible types: ") + aValue.typeName() + " * " +
    //                       bValue.typeName());
    //            }
    //            if (aValue.type() == StackValue::Type::INTEGER) {
    //                if (bValue.type() == StackValue::Type::INTEGER) {
    //                    _script->dataStack()->push(aValue.integerValue() * bValue.integerValue());
    //                } else {
    //                    _script->dataStack()->push((float) aValue.integerValue() * bValue.floatValue());
    //                }
    //            } else {
    //                if (bValue.type() == StackValue::Type::INTEGER) {
    //                    _script->dataStack()->push(aValue.floatValue() * (float) bValue.integerValue());
    //                } else {
    //                    _script->dataStack()->push(aValue.floatValue() * bValue.floatValue());
    //                }
    //            }
            }

            std::shared_ptr<IStackValue> StackValue::div(std::shared_ptr<IStackValue> value) const
            {
                // TODO
                return nullptr;
    //            Logger::debug("SCRIPT") << "[803C] [*] op_div /" << std::endl;
    //            auto bValue = _script->dataStack()->pop();
    //            auto aValue = _script->dataStack()->pop();
    //            if (!bValue.isNumber() || !aValue.isNumber()) {
    //                _error(std::string("op_div(a, b): Incompatible types: ") + aValue.typeName() + " / " +
    //                       bValue.typeName());
    //            }
    //            if (aValue.type() == StackValue::Type::INTEGER) {
    //                if (bValue.type() == StackValue::Type::INTEGER) {
    //                    _script->dataStack()->push(aValue.integerValue() / bValue.integerValue());
    //                } else {
    //                    _script->dataStack()->push((float) aValue.integerValue() / bValue.floatValue());
    //                }
    //            } else {
    //                if (bValue.type() == StackValue::Type::INTEGER) {
    //                    _script->dataStack()->push(aValue.floatValue() / (float) bValue.integerValue());
    //                } else {
    //                    _script->dataStack()->push(aValue.floatValue() / bValue.floatValue());
    //                }
    //            }
            }
        }
    }
}

