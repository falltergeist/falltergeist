// Project includes
#include "../../VM/Handler/Opcode812EHandler.h"
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
            Opcode812E::Opcode812E(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode812E::_run(VM::Script& script)
            {
                auto &debug = _logger->debug() << "[812E] [+] void obj_lock(GameObject* object)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (object) {
                    debug << "    PID: 0x" << std::hex << (object ? object->PID() : 0) << std::endl;
                    if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                        door->setLocked(true);
                    } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                        container->setLocked(true);
                    } else {
                        _warning(script, "obj_lock: object is not door or container");
                    }
                } else {
                    _warning(script, "obj_lock: object is null");
                }
            }
        }
    }
}
