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
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

// Falltergeist includes
#include "../Game/Object.h"
#include "../VM/VMErrorException.h"
#include "../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

VMStackValue::VMStackValue()
{
    _type = Type::INTEGER;
    _intValue = 0;
}

VMStackValue::VMStackValue(int value)
{
    _type = Type::INTEGER;
    _intValue = value;
}

VMStackValue::VMStackValue(float value)
{
    _type = Type::FLOAT;
    _floatValue = value;
}

VMStackValue::VMStackValue(const std::string &value)
{
    _type = Type::STRING;
    _stringValue = value;
}

VMStackValue::VMStackValue(Game::Object *value)
{
    //throw Exception("VMStackValue::VMStackValue(Game::GameObject*) - null object value is not allowed, use integer 0");
    _type = Type::OBJECT;
    _objectValue = value;
}

VMStackValue::~VMStackValue()
{
}

VMStackValue::Type VMStackValue::type() const
{
    return _type;
}

bool VMStackValue::isNumber() const
{
    return (_type == Type::FLOAT || _type == Type::INTEGER);
}

int VMStackValue::integerValue() const
{
    if (_type != Type::INTEGER) throw VMErrorException(std::string("VMStackValue::integerValue() - stack value is not integer, it is ") + typeName(_type));
    return _intValue;
}

float VMStackValue::floatValue() const
{
    if (_type != Type::FLOAT) throw VMErrorException(std::string("VMStackValue::floatValue() - stack value is not float, it is ") + typeName(_type));
    return _floatValue;
}

std::string VMStackValue::stringValue() const
{
    if (_type != Type::STRING) throw VMErrorException(std::string("VMStackValue::stringValue() - stack value is not string, it is ") + typeName(_type));
    return _stringValue;
}

Game::Object* VMStackValue::objectValue() const
{
    if (_type == Type::INTEGER && _intValue == 0)
    {
        return nullptr;
    }
    if (_type != Type::OBJECT) throw VMErrorException(std::string("VMStackValue::objectValue() - stack value is not an object, it is ") + typeName(_type));
    return _objectValue;
}

std::string VMStackValue::toString() const
{
    switch (_type)
    {
        case Type::INTEGER: return std::to_string(_intValue);
        case Type::FLOAT:
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(5) << _floatValue;
            return ss.str();
        }
        case Type::STRING:  return _stringValue;
        case Type::OBJECT:  return _objectValue ? _objectValue->name() : std::string("(null)"); // just in case, we should never create null object value
        default:
            throw VMErrorException("VMStackValue::toString() - cannot convert type to string: " + std::to_string((int)_type));
    }
}

int VMStackValue::toInteger() const
{
    switch (_type)
    {
        case Type::INTEGER: return _intValue;
        case Type::FLOAT:   return (int)_floatValue;
        case Type::STRING:
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
        case Type::OBJECT:  return (int)(_objectValue != nullptr);
        default:            return 0;
    }
}

bool VMStackValue::toBoolean() const
{
    switch (_type)
    {
        case Type::INTEGER:
            return _intValue != 0;
        case Type::FLOAT:
            return (bool)_floatValue;
        case Type::STRING:
            return _stringValue.length() > 0;
        case Type::OBJECT:
            return _objectValue != nullptr;
    }
    throw VMErrorException("VMStackValue::toBoolean() - something strange happened");
}

const char* VMStackValue::typeName() const
{
    return typeName(_type);
}

const char* VMStackValue::typeName(Type type)
{
    switch (type)
    {
        case Type::INTEGER: return "integer";
        case Type::FLOAT:   return "float";
        case Type::STRING:  return "string";
        case Type::OBJECT:  return "object";
        default:
            throw VMErrorException("VMStackValue::typeName() - no name for type: " + std::to_string((int)type));
    }
}


}
