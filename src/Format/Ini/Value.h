#pragma once

// Project includes

// Third-party includes

// stdlib
#include <ostream>
#include <string>

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            class Value;

            typedef std::vector<std::pair<std::string, Value>> Array;

            /**
             * @brief A value in INI file.
             * A wrapper for std::string with conversion functions to various types.
             */
            class Value
            {
                public:
                    Value(const std::string &value = "");

                    void operator =(const std::string&);

                    /*template <class T>
                    explicit operator T() const;*/

                    operator std::string() const;

                    const std::string& str() const;

                    int toInt() const;

                    double toDouble() const;

                    bool toBool() const;

                    Array toArray() const;


                private:
                    std::string _value;
            };

            inline std::ostream& operator <<(std::ostream& stream, const Value& value)
            {
                stream << value.str();
                return stream;
            }
        }
    }
}
