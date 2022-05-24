#pragma once

// Project includes

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist
{
    namespace Game
    {
        class Object;
    }
    namespace VM
    {
        class StackValue
        {
            public:
                enum class Type
                {
                    INTEGER = 1,
                    FLOAT,
                    STRING,
                    OBJECT
                };

                StackValue();

                StackValue(int value);

                StackValue(float value);

                StackValue(const std::string &value);

                StackValue(Game::Object *value);

                virtual ~StackValue();

                Type type() const;

                bool isNumber() const;

                // returns integer value or throws exception if it's not integer
                int32_t integerValue() const;

                // returns float value or throws exception if it's not float
                float floatValue() const;

                // returns string value or throws exception if it's not string
                std::string stringValue() const;

                // returns object pointer or throws exception if it's not object
                Game::Object *objectValue() const;

                // converts value of any type to string representation
                std::string toString() const;

                // converts any value to integer representation
                int32_t toInteger() const;

                bool toBoolean() const;

                const char *typeName() const;

                static const char *typeName(Type type);

            protected:
                Type _type = Type::INTEGER;
                union {
                    int32_t _intValue;
                    float _floatValue;
                    Game::Object *_objectValue;
                };
                std::string _stringValue;
        };
    }
}
