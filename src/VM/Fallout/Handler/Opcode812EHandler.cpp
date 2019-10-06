#include "Opcode812EHandler.h"
#include "Game/ContainerItemObject.h"
#include "Game/DoorSceneryObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode812E::applyTo(std::shared_ptr<IContext> context)
            {
                auto &debug = Logger::debug("SCRIPT") << "[812E] [+] void obj_lock(GameObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (object) {
                    debug << "    PID: 0x" << std::hex << (object ? object->PID() : 0) << std::endl;
                    if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                        door->setLocked(true);
                    } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                        container->setLocked(true);
                    } else {
                        _warning("obj_lock: object is not door or container");
                    }
                } else {
                    _warning("obj_lock: object is null");
                }
            }
        }
    }
}
