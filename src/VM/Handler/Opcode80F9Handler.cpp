#include "../../VM/Handler/Opcode80F9Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F9::Opcode80F9(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F9::_run()
            {
                logger->debug() << "[80F9] [=] void dialogue_system_enter()" << std::endl;
            }
        }
    }
}
