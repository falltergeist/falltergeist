// Project includes
#include "../../VM/Handler/Opcode812FHandler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DoorSceneryObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode812F::Opcode812F(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode812F::_run(VM::Script& script)
            {
                _logger->debug() << "[812F] [+] void obj_unlock(GameObject* object)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (object) {
                    if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                        door->setLocked(false);
                    } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                        container->setLocked(false);
                    } else {
                        _warning(script, "obj_unlock: object is not door or container");
                    }
                } else {
                    _warning(script, "obj_unlock: object is null");
                }
            }
        }
    }
}


