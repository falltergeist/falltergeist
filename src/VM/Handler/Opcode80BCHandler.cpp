// Project includes
#include "../../VM/Handler/Opcode80BCHandler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BC::Opcode80BC(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80BC::_run()
            {
                logger->debug() << "[80BC] [+] GameObject* self_obj()" << std::endl;
                _script->dataStack()->push(_script->owner());
            }
        }
    }
}
