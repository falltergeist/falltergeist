#include "../../VM/Handler/Opcode80F9Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F9::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80F9] [=] void dialogue_system_enter()" << std::endl;
            }
        }
    }
}
