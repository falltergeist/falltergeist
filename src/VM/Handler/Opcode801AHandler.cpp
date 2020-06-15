#include "../../VM/Handler/Opcode801AHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode801A::Opcode801A(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode801A::_run()
            {
                logger->debug() << "[801A] [*] op_pop" << std::endl;
                _script->dataStack()->pop();
            }
        }
    }
}
