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

#ifndef FALLTERGEIST_VM_ICONTEXT_H
#define FALLTERGEIST_VM_ICONTEXT_H

#include <memory>

namespace Falltergeist {
    namespace Game {
        class DudeObject;
    }
    namespace VM {
        class IContext {
        public:
            virtual ~IContext() = default;

            virtual std::shared_ptr<Game::DudeObject> player() = 0;
        };
    }
}

#endif //FALLTERGEIST_VM_ICONTEXT_H
