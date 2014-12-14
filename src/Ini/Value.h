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

#ifndef FALLTERGEIST_INI_VALUE_H
#define FALLTERGEIST_INI_VALUE_H

// C++ standard includes
#include <string>
#include <iosfwd>
#include <vector>

// Falltergeist includes

// Third party includes

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

    ~Value();

    Value & operator=(const Value &rhs);


    Value(double doubleVal);

    Value(int integerVal);

    Value(bool booleanVal);
    Value(std::string stringVal);
    Value(const Value &rhs);
    Value(std::vector<Value> iniVal);

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

} // Ini
} // Falltergeist

#endif // FALLTERGEIST_INI_VALUE_H
