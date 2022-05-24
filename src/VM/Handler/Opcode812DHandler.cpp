// Project includes
#include "../../VM/Handler/Opcode812DHandler.h"
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
            Opcode812D::Opcode812D(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode812D::_run()
            {
                logger->debug() << "[812D] [+] int is_locked(GameDoorSceneryObject* object)" << std::endl;
                auto object = dynamic_cast<Game::DoorSceneryObject *>(_script->dataStack()->popObject());
                _script->dataStack()->push(object->locked());
            }
        }
    }
}


