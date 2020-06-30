#include "../../VM/Handler/Opcode801BHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode801B::Opcode801B(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode801B::_run()
            {
                logger->debug() << "[801B] op_dup" << std::endl;
                _script->dataStack()->push(_script->dataStack()->top());
            }
        }
    }
}
