// Project includes
#include "../Ini/Parser.h"
#include "../../Exception.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            Value::Value(const std::string& value) : _value(value)
            {
            }

            void Value::operator =(const std::string& value)
            {
                _value = value;
            }

            Value::operator std::string() const
            {
                return _value;
            }

            const std::string& Value::str() const
            {
                return _value;
            }

            int Value::toInt() const
            {
                try
                {
                    return std::stoi(_value);
                }
                catch (const std::invalid_argument&)
                {
                    return 0;
                }
            }

            double Value::toDouble() const
            {
                try
                {
                    return std::stod(_value);
                }
                catch (const std::invalid_argument&)
                {
                    return 0.0;
                }
            }

            bool Value::toBool() const
            {
                std::string lc = _value;
                Parser::toLower(lc);
                return (lc == "on" || lc == "true");
            }

            Array Value::toArray() const
            {
                return Parser::parseArray(_value);
            }
        }
    }
}
