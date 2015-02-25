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

#ifndef FALLTERGEIST_VMSTACKVALUE_H
#define FALLTERGEIST_VMSTACKVALUE_H

// C++ standard includes
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
    
<<<<<<< HEAD
namespace Game { class GameObject; };
=======
class Game::GameObject;
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts

class VMStackValue
{
protected:
    int _type = 0;
    union
    {
        int _intValue;
        float _floatValue;
<<<<<<< HEAD
        Game::GameObject* _objectValue;
    };
    std::string _stringValue;
=======
        std::string _stringValue;
        Game::GameObject* _objectValue;
    };
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
public:
    enum { TYPE_INTEGER = 1, TYPE_FLOAT, TYPE_STRING, TYPE_OBJECT };
    VMStackValue();
    VMStackValue(int value);
    VMStackValue(float value);
    VMStackValue(const std::string &value);
    VMStackValue(Game::GameObject *value);
    virtual ~VMStackValue();
    int type() const;
<<<<<<< HEAD
    bool isNumber() const;
    // returns integer value or throws exception if it's not integer
    int integerValue() const;
    // returns float value or throws exception if it's not float
    float floatValue() const;
    // returns string value or throws exception if it's not string
    std::string stringValue() const;
    // returns object pointer or throws exception if it's not object
    Game::GameObject* objectValue() const;
    
    // converts value of any type to string representation
    std::string toString() const;
    // converts any value to integer representation
    int toInteger() const;
    bool toBoolean() const;
    
    const char* typeName();
    static const char* typeName(int type);
=======
    int integerValue() const;
    float floatValue() const;
    std::string stringValue() const;
    Game::GameObject* objectValue() const;
    std::string toString() const;
    
    static const std::string typeName(int type);
>>>>>>> VM type system refactoring: make one class for all types, all stacks will contain values directly. No pointers and dynamic_casts
};

}
#endif // FALLTERGEIST_VMSTACKVALUE_H
