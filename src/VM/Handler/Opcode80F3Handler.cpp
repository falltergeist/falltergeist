#include "../../VM/Handler/Opcode80F3Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F3::Opcode80F3(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F3::_run()
            {
                logger->debug() << "[80F3] [=] int has_trait(int type,void* who, int trait)" << std::endl;
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->popInteger();
                dataStack->push(1);
            }
        }
    }
}
