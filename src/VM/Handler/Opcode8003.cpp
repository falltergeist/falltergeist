#include "../../VM/Handler/Opcode8003.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8003::Opcode8003(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8003::_run()
            {
                logger->debug() << "[8003] op_critical_done" << std::endl;
            }
        }
    }
}
