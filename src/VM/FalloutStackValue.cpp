/*
 * Copyright 2012-2018 Falltergeist Developers.
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
#include "FalloutStackValue.h"

// Falltergeist includes

// Third party includes

namespace Falltergeist {
    namespace VM {
        FalloutStackValue::FalloutStackValue(int value) {
            _type = Type::INTEGER;
            _integerValue = value;
        }

        FalloutStackValue::FalloutStackValue(const std::string &value) {
            _type = Type::STRING;
            _stringValue = value;
        }

        FalloutStackValue::Type FalloutStackValue::type() const {
            return _type;
        }

        int FalloutStackValue::asInteger() const {
            return _integerValue;
        }

        std::string FalloutStackValue::asString() const {
            return _stringValue;
        }
    }
}

