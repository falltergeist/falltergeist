#include "../../VM/Handler/Opcode80C7Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C7::Opcode80C7(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C7::_run()
            {
                logger->debug() << "[80C7] [*] int script_action()" << std::endl;
                _script->dataStack()->push(21);
            }
        }
    }
}
