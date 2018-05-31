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

// Falltergeist includes
#include "../Exception.h"
#include "../VM/FalloutStack.h"
#include "FalloutValue.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        void FalloutStack::push(std::shared_ptr<IFalloutValue> value) {
            _values.push_back(value);
        }

        void FalloutStack::push(int value) {
            _values.push_back(std::make_shared<FalloutValue>(value));
        }

        std::shared_ptr<IFalloutValue> FalloutStack::at(int offset) {
            return _values.at(offset);
        }

        std::shared_ptr<IFalloutValue> FalloutStack::pop() {
            if (_values.size() == 0) {
                throw Exception("FalloutStack::pop() - stack is empty");
            }
            auto value = _values.back();
            _values.pop_back();
            return value;
        }

        std::shared_ptr<IFalloutValue> FalloutStack::top() {
            return _values.back();
        }

        void FalloutStack::clear() {
            _values.clear();
        }

        size_t FalloutStack::size() {
            return _values.size();
        }

        void FalloutStack::swap() {
            if (_values.size() < 2) {
                throw Exception("FalloutStack::swap() - stack size is lesser than 2");
            }

            auto value1 = _values.back();
            _values.pop_back();
            auto value2 = _values.back();
            _values.pop_back();
            _values.push_back(value1);
            _values.push_back(value2);
        }
    }
}