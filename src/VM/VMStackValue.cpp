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

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../VM/VMStackValue.h"
#include "../Exception.h"
#include "../Game/Object.h"

// Third party includes

namespace Falltergeist
{

VMStackValue::VMStackValue()
{
    _type = TYPE_INTEGER;
    _intValue = 0;
}

VMStackValue::VMStackValue(int value)
{
    _type = TYPE_INTEGER;
    _intValue = value;
}

VMStackValue::VMStackValue(float value)
{
    _type = TYPE_FLOAT;
    _floatValue = value;
}

VMStackValue::VMStackValue(const std::string &value)
{
    _type = TYPE_STRING;
    _stringValue = value;
}

VMStackValue::VMStackValue(Game::GameObject *value)
{
    //throw Exception("VMStackValue::VMStackValue(Game::GameObject*) - null object value is not allowed, use integer 0");
    _type = TYPE_OBJECT;
    _objectValue = value;
}

VMStackValue::~VMStackValue()
{
}

int VMStackValue::type() const
{
    return _type;
}

bool VMStackValue::isNumber() const
{
    return (_type == TYPE_FLOAT || _type == TYPE_INTEGER);
}

int VMStackValue::integerValue() const
{
    if (_type != TYPE_INTEGER) throw Exception(std::string("VMStackValue::integerValue() - stack value is not integer, it is ") + typeName(_type));
    return _intValue;
}

float VMStackValue::floatValue() const
{
    if (_type != TYPE_FLOAT) throw Exception(std::string("VMStackValue::floatValue() - stack value is not float, it is ") + typeName(_type));
    return _floatValue;
}

std::string VMStackValue::stringValue() const
{
    if (_type != TYPE_STRING) throw Exception(std::string("VMStackValue::stringValue() - stack value is not string, it is ") + typeName(_type));
    return _stringValue;
}

Game::GameObject* VMStackValue::objectValue() const
{
    if (_type != TYPE_OBJECT) throw Exception(std::string("VMStackValue::objectValue() - stack value is not an object, it is ") + typeName(_type));
    return _objectValue;
}

std::string VMStackValue::toString() const
{
    switch (_type)
    {
        case TYPE_INTEGER: return std::to_string(_intValue);
        case TYPE_FLOAT:   return std::to_string(_floatValue);
        case TYPE_STRING:  return _stringValue;
        case TYPE_OBJECT:  return _objectValue ? _objectValue->name() : std::string("(null)"); // just in case, we should never create null object value
        default:
            throw Exception("VMStackValue::toString() - wrong type: " + std::to_string(_type));
    }
}

int VMStackValue::toInteger() const
{
    switch (_type)
    {
        case TYPE_INTEGER: return _intValue;
        case TYPE_FLOAT:   return (int)_floatValue;
        case TYPE_STRING: 
        {
            int result = 0;
            try 
            {
                result = std::stoi(_stringValue, nullptr, 0);
            }
            catch (std::invalid_argument ex) { }
            catch (std::out_of_range ex) { }
            return result;
        }
        case TYPE_OBJECT:  return (int)(_objectValue != nullptr);
        default:
            throw Exception("VMStackValue::toInteger() - wrong type: " + std::to_string(_type));
    }
}

bool VMStackValue::toBoolean() const
{
    switch (_type)
    {
        case TYPE_INTEGER:
            return _intValue != 0;
        case TYPE_FLOAT:
            return (bool)_floatValue;
        case TYPE_STRING:
            return _stringValue.length() > 0;
        case TYPE_OBJECT:
            return _objectValue != nullptr;
    }
    throw Exception("VMStackValue::toBoolean() - something strange happened");
}

const char* VMStackValue::typeName()
{
    return typeName(_type);
}

const char* VMStackValue::typeName(int type)
{
    switch (type)
    {
        case TYPE_INTEGER: return "integer";
        case TYPE_FLOAT:   return "float";
        case TYPE_STRING:  return "string";
        case TYPE_OBJECT:  return "object";
        default:
            throw Exception("VMStackValue::typeName() - wrong type: " + std::to_string(type));
    }
}


}
