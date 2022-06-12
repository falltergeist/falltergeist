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
            Opcode810D::Opcode810D(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode810D::_run(VM::Script& script)
            {
                _logger->debug() << "[810D] [=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
                const int pid = script.dataStack()->popInteger();
                auto who = script.dataStack()->popObject();

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
                    script.dataStack()->push(findItem(critter->inventory()));
                } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(who)) {
                    script.dataStack()->push(findItem(container->inventory()));
                } else {
                    _warning(script, std::string("obj_carrying_pid_obj: 'who' is not valid GameCritterObject, nor ContainerItemObject. It is ") +
                             typeid(who).name());
                    script.dataStack()->push(nullptr);
                }
            }
        }
    }
}
