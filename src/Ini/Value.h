#pragma once

#include <string>
#include <iosfwd>
#include <vector>

namespace Falltergeist
{
    namespace Ini
    {
        class Value
        {
            public:
                enum class Tag
                {
                    DOUBLE,
                    INTEGER,
                    BOOLEAN,
                    STRING,
                    ARRAY
                };

                Value();
                Value(double doubleVal);
                Value(int integerVal);
                Value(bool booleanVal);
                Value(const std::string& stringVal);
                Value(const Value &rhs);
                Value(std::vector<Value> iniVal);
                ~Value();

                Value & operator=(const Value &rhs);

                Value::Tag tag() const;
                static std::string tagString(Value::Tag tag);
                std::string value() const;
                int intValue() const;
                bool boolValue() const;
                double doubleValue() const;

                friend class Section;
            private:
                Tag _tag;

                union
                {
                    double _doubleVal;
                    int _integerVal;
                    bool _booleanVal;
                    std::string _stringVal;
                    std::vector<Value> _iniVal;
                };
        };
    }
}
