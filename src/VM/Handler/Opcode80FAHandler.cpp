#include "../../VM/Handler/Opcode80FAHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80FA::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80FA] [+] int action_being_used()" << std::endl;
                _script->dataStack()->push((signed) _script->usedSkill());
            }
        }
    }
}
