#include "Opcode80F7Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F7::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80F7] [=] int fixed_param()" << std::endl;
                _script->dataStack()->push(_script->fixedParam());
            }
        }
    }
}


