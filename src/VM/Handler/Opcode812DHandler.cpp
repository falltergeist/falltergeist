#include "../../VM/Handler/Opcode812DHandler.h"
#include "../../Game/DoorSceneryObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode812D::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[812D] [+] int is_locked(GameDoorSceneryObject* object)" << std::endl;
                auto object = dynamic_cast<Game::DoorSceneryObject *>(_script->dataStack()->popObject());
                _script->dataStack()->push(object->locked());
            }
        }
    }
}


