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

#ifndef FALLTERGEIST_VM_IFALLOUTSTACK_H
#define FALLTERGEIST_VM_IFALLOUTSTACK_H

// C++ standard includes
#include <memory>
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist {
    namespace VM {
        class IFalloutStackValue;

        class IFalloutStack {
        public:
            virtual ~IFalloutStack() = default;

            virtual void push(std::shared_ptr<IFalloutStackValue> value) = 0;

            virtual void push(int value) = 0;

            virtual std::shared_ptr<IFalloutStackValue> at(int offset) = 0;

            virtual std::shared_ptr<IFalloutStackValue> pop() = 0;

            virtual std::shared_ptr<IFalloutStackValue> top() = 0;

            virtual void clear() = 0;

            virtual size_t size() = 0;

            virtual void swap() = 0;

            virtual int stackBase() = 0;

            virtual void rememberStackBase() = 0;
        };
    }
}

#endif //FALLTERGEIST_VM_IFALLOUTSTACK_H
