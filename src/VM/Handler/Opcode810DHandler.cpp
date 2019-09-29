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
#include "../../VM/Handler/Opcode810DHandler.h"

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/ItemObject.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode810D::Opcode810D(VM::Script *script) : OpcodeHandler(script) {
            }

            void Opcode810D::_run() {
                Logger::debug("SCRIPT") << "[810D] [=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
                const int pid = _script->dataStack()->popInteger();
                auto who = _script->dataStack()->popObject();

                auto findItem = [&](std::vector<Game::ItemObject *> *container) -> Game::ItemObject* {
                    auto iterator = std::find_if(container->begin(), container->end(),
                                                 [&](Game::ItemObject *&item) { return item->PID() == pid; });
                    if (iterator != container->end()) {
                        return *iterator;
                    } else {
                        return nullptr;
                    }
                };

                if (auto critter = dynamic_cast<Game::CritterObject *>(who)) {
                    _script->dataStack()->push(findItem(critter->inventory()));
                } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(who)) {
                    _script->dataStack()->push(findItem(container->inventory()));
                } else {
                    _warning(std::string("obj_carrying_pid_obj: 'who' is not valid GameCritterObject, nor ContainerItemObject. It is ") +
                             typeid(who).name());
                    _script->dataStack()->push(nullptr);
                }
            }
        }
    }
}
