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
    
class Game::GameObject;

class VMStackValue
{
protected:
    int _type = 0;
    union
    {
        int _intValue;
        float _floatValue;
        std::string _stringValue;
        Game::GameObject* _objectValue;
    };
public:
    enum { TYPE_INTEGER = 1, TYPE_FLOAT, TYPE_STRING, TYPE_OBJECT };
    VMStackValue();
    VMStackValue(int value);
    VMStackValue(float value);
    VMStackValue(const std::string &value);
    VMStackValue(Game::GameObject *value);
    virtual ~VMStackValue();
    int type() const;
    int integerValue() const;
    float floatValue() const;
    std::string stringValue() const;
    Game::GameObject* objectValue() const;
    std::string toString() const;
    
    static const std::string typeName(int type);
};

}
#endif // FALLTERGEIST_VMSTACKVALUE_H
