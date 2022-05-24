// Project includes
#include "../../VM/Handler/Opcode8002.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8002::Opcode8002(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8002::_run()
            {
                logger->debug() << "[8002] op_critical_start" << std::endl;
            }
        }
    }
}
