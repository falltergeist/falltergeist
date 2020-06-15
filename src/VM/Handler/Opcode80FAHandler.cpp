#include "../../VM/Handler/Opcode80FAHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80FA::Opcode80FA(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80FA::_run()
            {
                logger->debug() << "[80FA] [+] int action_being_used()" << std::endl;
                _script->dataStack()->push((signed) _script->usedSkill());
            }
        }
    }
}
