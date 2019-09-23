#include "../../VM/Handler/Opcode80F3Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F3::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80F3] [=] int has_trait(int type,void* who, int trait)" << std::endl;
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->popInteger();
                dataStack->push(1);
            }
        }
    }
}
