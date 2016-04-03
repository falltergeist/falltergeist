/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef FALLTERGEIST_VM_STACKVALUE_H
#define FALLTERGEIST_VM_STACKVALUE_H

// C++ standard includes
#include <string>

// Falltergeist includes

// Third party includes

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
                int integerValue() const;
                // returns float value or throws exception if it's not float
                float floatValue() const;
                // returns string value or throws exception if it's not string
                std::string stringValue() const;
                // returns object pointer or throws exception if it's not object
                Game::Object* objectValue() const;

                // converts value of any type to string representation
                std::string toString() const;
                // converts any value to integer representation
                int toInteger() const;
                bool toBoolean() const;

                const char* typeName() const;
                static const char* typeName(Type type);

            protected:
                Type _type = Type::INTEGER;
                union
                {
                    int _intValue;
                    float _floatValue;
                    Game::Object* _objectValue;
                };
                std::string _stringValue;

        };
    }
}
#endif // FALLTERGEIST_VM_STACKVALUE_H
