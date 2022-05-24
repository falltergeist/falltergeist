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
            Opcode80F7::Opcode80F7(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F7::_run()
            {
                logger->debug() << "[80F7] [=] int fixed_param()" << std::endl;
                _script->dataStack()->push(_script->fixedParam());
            }
        }
    }
}


