#include "../../VM/Handler/Opcode803EHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803E::Opcode803E(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode803E::_run()
            {
                logger->debug() << "[803E] [*] op_and" << std::endl;
                auto b = _script->dataStack()->popLogical();
                auto a = _script->dataStack()->popLogical();
                _script->dataStack()->push(a && b); // integer 1 or 0
            }
        }
    }
}
