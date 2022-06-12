// Project includes
#include "../../VM/Handler/Opcode80F3Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F3::Opcode80F3(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F3::_run(VM::Script& script)
            {
                _logger->debug() << "[80F3] [=] int has_trait(int type,void* who, int trait)" << std::endl;
                auto dataStack = script.dataStack();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->popInteger();
                dataStack->push(1);
            }
        }
    }
}
