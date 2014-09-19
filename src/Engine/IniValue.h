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
 *
 */

#ifndef FALLTERGEIST_INI_VALUE_H
#define FALLTERGEIST_INI_VALUE_H

// C++ standard includes
#include <string>
#include <iosfwd>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{

class IniValue
{
public:
    enum class Tag
    {
        DOUBLE,
        INTEGER,
        BOOLEAN,
        STRING
    };

    IniValue();

    ~IniValue();

    IniValue & operator=(const IniValue &rhs);


    IniValue(double doubleVal);

    IniValue(int integerVal);

    IniValue(bool booleanVal);
    IniValue(std::string stringVal);
    IniValue(const IniValue &rhs);

    friend class IniSection;
    friend std::ostream &operator << (std::ostream &os, const IniValue &iv);
private:
    Tag _tag;

    union
    {
        double _doubleVal;
        int _integerVal;
        bool _booleanVal;
        std::string _stringVal;
    };
};

}

#endif // FALLTERGEIST_INI_VALUE_H