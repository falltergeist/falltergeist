#include "../../VM/Handler/Opcode8153Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8153::Opcode8153(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8153::_run()
            {
                logger->debug() << "[8153] [=] void terminate_combat()" << std::endl;
            }
        }
    }
}
