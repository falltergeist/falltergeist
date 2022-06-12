// Project includes
#include "../../VM/Handler/Opcode80F9Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F9::Opcode80F9(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F9::_run(VM::Script& script)
            {
                _logger->debug() << "[80F9] [=] void dialogue_system_enter()" << std::endl;
            }
        }
    }
}
