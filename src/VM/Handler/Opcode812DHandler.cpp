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
            Opcode812D::Opcode812D(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode812D::_run(VM::Script& script)
            {
                _logger->debug() << "[812D] [+] int is_locked(GameDoorSceneryObject* object)" << std::endl;
                auto object = dynamic_cast<Game::DoorSceneryObject *>(script.dataStack()->popObject());
                script.dataStack()->push(object->locked());
            }
        }
    }
}


