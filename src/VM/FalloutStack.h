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

#ifndef FALLTERGEIST_VM_FALLOUTSTACK_H
#define FALLTERGEIST_VM_FALLOUTSTACK_H

// C++ standard includes

// Falltergeist includes
#include "../VM/IFalloutStack.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        class FalloutStack : public virtual IFalloutStack {
        public:
            virtual ~FalloutStack() = default;

            void push(std::shared_ptr<IFalloutValue> value) override;

            void push(int value) override;

            std::shared_ptr<IFalloutValue> at(int offset) override;

            std::shared_ptr<IFalloutValue> pop() override;

            std::shared_ptr<IFalloutValue> top() override;

            void clear() override;

            size_t size() override;

            void swap() override;

        private:
            std::vector<std::shared_ptr<IFalloutValue>> _values;
        };
    }
}

#endif //FALLTERGEIST_VM_FALLOUTSTACK_H
