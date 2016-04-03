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

// Related headers
#include "../VM/Stack.h"

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Exception.h"
#include "../VM/StackValue.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        Stack::Stack()
        {
        }

        Stack::~Stack()
        {
        }

        void Stack::push(const StackValue& value)
        {
            _values.push_back(value);
        }

        const StackValue Stack::pop()
        {
            if (_values.size() == 0) throw Exception("Stack::pop() - stack is empty");
            auto value = _values.back();
            _values.pop_back();
            return value;
        }

        int Stack::size()
        {
            return _values.size();
        }

        void Stack::swap()
        {
            if (_values.size() < 2) throw Exception("Stack::swap() - size is < 2");

            auto value1 = _values.back(); _values.pop_back();
            auto value2 = _values.back(); _values.pop_back();
            _values.push_back(value1);
            _values.push_back(value2);
        }

        std::vector<StackValue>* Stack::values()
        {
            return &_values;
        }

        const StackValue Stack::top()
        {
            return _values.back();
        }

        int Stack::popInteger()
        {
            return pop().integerValue();
        }

        void Stack::push(unsigned int value)
        {
            push((int)value);
        }

        void Stack::push(int value)
        {
            push(StackValue(value));
        }

        float Stack::popFloat()
        {
            return pop().floatValue();
        }

        void Stack::push(float value)
        {
            push(StackValue(value));
        }

        Game::Object* Stack::popObject()
        {
            return pop().objectValue();
        }

        void Stack::push(Game::Object* value)
        {
            push(StackValue(value));
        }

        std::string Stack::popString()
        {
            return pop().stringValue();
        }

        void Stack::push(const std::string &value)
        {
            push(StackValue(value));
        }

        bool Stack::popLogical()
        {
            return pop().toBoolean();
        }
    }
}
