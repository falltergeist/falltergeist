#include "../Exception.h"
#include "../VM/FalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        FalloutValue::FalloutValue(int value)
        {
            _type = Type::INTEGER;
            _integerValue = value;
            _floatValue = (float) value;
            _stringValue = std::to_string(value);
        }

        FalloutValue::FalloutValue(float value)
        {
            _type = Type::FLOAT;
            _integerValue = (int) value;
            _floatValue = value;
            _stringValue = std::to_string(value);
        }

        FalloutValue::FalloutValue(const std::string &value)
        {
            _type = Type::STRING;
            _integerValue = std::stoi(value);
            _floatValue = std::stof(value);
            _stringValue = value;
        }

        FalloutValue::Type FalloutValue::type() const
        {
            return _type;
        }

        int FalloutValue::asInteger() const
        {
            return _integerValue;
        }

        float FalloutValue::asFloat() const
        {
            return _floatValue;
        }

        std::string FalloutValue::asString() const
        {
            return _stringValue;
        }

        std::shared_ptr<IFalloutValue> FalloutValue::add(std::shared_ptr<IFalloutValue> value) const
        {
            if (type() == Type::INTEGER  && value->type() == Type::INTEGER) {
                int sum = asInteger() + value->asInteger();
                return std::make_shared<FalloutValue>(sum);
            }

            if (type() == Type::INTEGER && value->type() == Type::FLOAT) {
                float sum = asFloat() + value->asFloat();
                return std::make_shared<FalloutValue>(sum);
            }

            if (type() == Type::INTEGER && value->type() == Type::STRING) {
                int sum = asInteger() + value->asInteger();
                return std::make_shared<FalloutValue>(sum);
            }

            if (type() == Type::FLOAT) {
                float sum = asFloat() + value->asFloat();
                return std::make_shared<FalloutValue>(sum);
            }

            if (type() == Type::STRING) {
                std::string sum = asString() + value->asString();
                return std::make_shared<FalloutValue>(sum);
            }

            throw Exception("Invalid operand types");
        }
    }
}

