// Project includes
#include "../../VM/Handler/Opcode80F7Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F7::Opcode80F7(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F7::_run(VM::Script& script)
            {
                _logger->debug() << "[80F7] [=] int fixed_param()" << std::endl;
                script.dataStack()->push(script.fixedParam());
            }
        }
    }
}


