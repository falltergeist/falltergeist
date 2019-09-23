#include "../../VM/Handler/Opcode8153Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8153::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[8153] [=] void terminate_combat()" << std::endl;
            }
        }
    }
}
