// Project includes
#include "../../VM/Handler/Opcode8100Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Game/ObjectFactory.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8100::Opcode8100(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8100::_run()
            {
                logger->debug() << "[8100] [+] int obj_pid(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _script->dataStack()->push(0);
                } else {
                    _script->dataStack()->push(object->PID());
                }
            }
        }
    }
}


