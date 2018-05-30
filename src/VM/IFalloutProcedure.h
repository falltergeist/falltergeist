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

#ifndef FALLTERGEIST_VM_IFALLOUTPROCEDURE_H
#define FALLTERGEIST_VM_IFALLOUTPROCEDURE_H

// C++ standard includes
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist {
    namespace VM {
        class IFalloutProcedure {
        public:
            virtual uint32_t flags() const = 0;

            virtual uint32_t delay() const = 0;

            virtual uint32_t conditionOffset() const = 0;

            virtual uint32_t bodyOffset() const = 0;

            virtual uint32_t argumentsCounter() = 0;

            virtual std::string name() const = 0;

            virtual bool isTimed() = 0;

            virtual bool isConditional() = 0;

            virtual bool isImported() = 0;

            virtual bool isExported() = 0;

            virtual bool isCritical() = 0;

            virtual bool isPure() = 0;

            virtual bool isInline() = 0;
        };
    }
}


#endif //FALLTERGEIST_VM_IFALLOUTPROCEDURE_H
