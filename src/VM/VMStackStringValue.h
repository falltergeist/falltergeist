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

#ifndef FALLTERGEIST_VMSTACKPOINTERVALUE_H
#define FALLTERGEIST_VMSTACKPOINTERVALUE_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../VM/VMStackValue.h"

// Third party includes

namespace Falltergeist
{

class VMStackStringValue  : public VMStackValue
{
protected:
    std::string _value;
public:
    VMStackStringValue(std::string value);
    virtual ~VMStackStringValue();
    void setValue(std::string value);
    std::string value();

};

}
#endif // FALLTERGEIST_VMSTACKPOINTERVALUE_H
