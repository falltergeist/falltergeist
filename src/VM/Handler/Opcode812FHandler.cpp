#include "../../VM/Handler/Opcode812FHandler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DoorSceneryObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode812F::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[812F] [+] void obj_unlock(GameObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (object) {
                    if (auto door = dynamic_cast<Game::DoorSceneryObject *>(object)) {
                        door->setLocked(false);
                    } else if (auto container = dynamic_cast<Game::ContainerItemObject *>(object)) {
                        container->setLocked(false);
                    } else {
                        _warning("obj_unlock: object is not door or container");
                    }
                } else {
                    _warning("obj_unlock: object is null");
                }
            }
        }
    }
}


