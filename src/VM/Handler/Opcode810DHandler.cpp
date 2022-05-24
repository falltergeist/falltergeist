// Project includes
#include "../../VM/Handler/Opcode810DHandler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/ItemObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib
#include <algorithm>

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810D::Opcode810D(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode810D::_run()
            {
                logger->debug() << "[810D] [=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
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
