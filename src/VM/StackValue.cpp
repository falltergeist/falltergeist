#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include "../Game/Object.h"
#include "../VM/ErrorException.h"
#include "../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        StackValue::StackValue()
        {
            _type = Type::INTEGER;
            _intValue = 0;
        }

        StackValue::StackValue(int value)
        {
            _type = Type::INTEGER;
            _intValue = value;
        }

        StackValue::StackValue(float value)
        {
            _type = Type::FLOAT;
            _floatValue = value;
        }

        StackValue::StackValue(const std::string &value)
        {
            _type = Type::STRING;
            _stringValue = value;
        }

        StackValue::StackValue(const std::shared_ptr<Game::Object> &value)
        {
            //throw Exception("StackValue::StackValue(Game::GameObject*) - null object value is not allowed, use integer 0");
            _type = Type::OBJECT;
            _objectValue = value;
        }

        StackValue::~StackValue()
        {
        }

        StackValue::Type StackValue::type() const
        {
            return _type;
        }

        bool StackValue::isNumber() const
        {
            return (_type == Type::FLOAT || _type == Type::INTEGER);
        }

        int StackValue::integerValue() const
        {
            if (_type != Type::INTEGER) {
                throw ErrorException(std::string("StackValue::integerValue() - stack value is not integer, it is ") +
                                     typeName(_type));
            }
            return _intValue;
        }

        float StackValue::floatValue() const
        {
            if (_type != Type::FLOAT) {
                throw ErrorException(
                    std::string("StackValue::floatValue() - stack value is not float, it is ") + typeName(_type));
            }
            return _floatValue;
        }

        std::string StackValue::stringValue() const
        {
            if (_type != Type::STRING) {
                throw ErrorException(
                    std::string("StackValue::stringValue() - stack value is not string, it is ") + typeName(_type));
            }
            return _stringValue;
        }

        std::shared_ptr<Game::Object> StackValue::objectValue() const
        {
            if (_type == Type::INTEGER && _intValue == 0) {
                return nullptr;
            }
            if (_type != Type::OBJECT) {
                throw ErrorException(std::string("StackValue::objectValue() - stack value is not an object, it is ") +
                                     typeName(_type));
            }
            return _objectValue;
        }

        std::string StackValue::toString() const
        {
            switch (_type) {
                case Type::INTEGER:
                    return std::to_string(_intValue);
                case Type::FLOAT: {
                    std::stringstream ss;
                    ss << std::fixed << std::setprecision(5) << _floatValue;
                    return ss.str();
                }
                case Type::STRING:
                    return _stringValue;
                case Type::OBJECT:
                    return _objectValue ? _objectValue->name() : std::string(
                            "(null)"); // just in case, we should never create null object value
                default:
                    throw ErrorException(
                            "StackValue::toString() - cannot convert type to string: " + std::to_string((int) _type));
            }
        }

        int StackValue::toInteger() const
        {
            switch (_type) {
                case Type::INTEGER:
                    return _intValue;
                case Type::FLOAT:
                    return (int) _floatValue;
                case Type::STRING: {
                    int result = 0;
                    try {
                        result = std::stoi(_stringValue, nullptr, 0);
                    }
                    catch (const std::invalid_argument &) {}
                    catch (const std::out_of_range &) {}
                    return result;
                }
                case Type::OBJECT:
                    return (int) (_objectValue != nullptr);
                default:
                    return 0;
            }
        }

        bool StackValue::toBoolean() const
        {
            switch (_type) {
                case Type::INTEGER:
                    return _intValue != 0;
                case Type::FLOAT:
                    return (bool) _floatValue;
                case Type::STRING:
                    return _stringValue.length() > 0;
                case Type::OBJECT:
                    return _objectValue != nullptr;
            }
            throw ErrorException("StackValue::toBoolean() - something strange happened");
        }

        const char *StackValue::typeName() const
        {
            return typeName(_type);
        }

        const char *StackValue::typeName(Type type)
        {
            switch (type) {
                case Type::INTEGER:
                    return "integer";
                case Type::FLOAT:
                    return "float";
                case Type::STRING:
                    return "string";
                case Type::OBJECT:
                    return "object";
                default:
                    throw ErrorException("StackValue::typeName() - no name for type: " + std::to_string((int) type));
            }
        }
    }
}
